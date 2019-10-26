//=====================================
//
//FieldController.cpp
//�@�\:�t�B�[���h�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldController.h"
#include "FieldCursor.h"
#include "FieldGround.h"
#include "Place\FieldPlaceContainer.h"
#include "Place\OperatePlaceContainer.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "Route\RouteProcessor.h"
#include "PlaceActorController.h"
#include "FieldEventHandler.h"

#include "Controller\FieldDevelopper.h"
#include "Controller\FieldInput.h"

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

#include <algorithm>

#include "../Effect/GameParticleManager.h"

namespace Field
{
	/**************************************
	static�����o
	***************************************/
	const float FieldController::PlaceOffset = 10.0f;				//Place��1�}�X���̃I�t�Z�b�g�l
	const int FieldController::InitFieldBorder = 30;				//�t�B�[���h�͈͂̏����l
	const int FieldController::DevelopmentInterval = 30;			//���W���x���㏸�̃C���^�[�o��
	const float FieldController::MaxDevelopmentLevelAI = 9999.0f;	//AI���W���x���̍ő�l

	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder),
		cntFrame(0),
		developmentLevelAI(0),
		developSpeedBonus(1.0f),
		onConnectTown(nullptr),
		onCreateJunction(nullptr),
		onChangePlaceType(nullptr)
	{
		using Model::PlaceContainer;
		using Model::PlaceModel;

		//�C���X�^���X�쐬
		cursor = new FieldCursor(PlaceOffset);
		ground = new FieldGround();
		placeContainer = new Model::PlaceContainer();
		operateContainer = new Model::OperatePlaceContainer();
		placeActController = new Actor::PlaceActorController();
		developper = new FieldDevelopper(this);
		input = new FieldInput(this);

		//�X�e�[�g�}�V���쐬
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState();
		fsm[State::Develop] = new UseItemState();

		//�f���Q�[�g�쐬
		onConnectTown = DelegateObject<PlaceContainer, void(const PlaceModel*)>::Create(placeContainer, &PlaceContainer::OnConnectedTown);
		onCreateJunction = DelegateObject<PlaceContainer, void(const PlaceModel*)>::Create(placeContainer, &PlaceContainer::OnCreateJunction);
		onChangePlaceType = DelegateObject<Actor::PlaceActorController, void(const PlaceModel*)>::Create(placeActController, &Actor::PlaceActorController::ChangeActor);

		//���[�g�v���Z�b�T�쐬
		routeProcessor = new Model::RouteProcessor(onChangePlaceType);

		//�������ԏ�����
		//TODO:�V�[�����ׂ��ň����p����悤�ɂ���

		//�X�e�[�g������
		ChangeState(State::Idle);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	FieldController::~FieldController()
	{
		routeContainer.clear();

		//�C���X�^���X�폜
		SAFE_DELETE(cursor);
		SAFE_DELETE(ground);
		SAFE_DELETE(placeContainer);
		SAFE_DELETE(operateContainer);
		SAFE_DELETE(routeProcessor);
		SAFE_DELETE(placeActController);
		SAFE_DELETE(developper);
		SAFE_DELETE(input);

		//�f���Q�[�g�폜
		SAFE_DELETE(onConnectTown);
		SAFE_DELETE(onCreateJunction);
		SAFE_DELETE(onChangePlaceType);

		//�X�e�[�g�}�V���폜
		Utility::DeleteContainer(fsm);
	}

	/**************************************
	�I�u�W�F�N�g�X�V����
	***************************************/
	void FieldController::UpdateObject()
	{
		//�e�X�V����
		cursor->Update();
		placeContainer->Update();

		placeActController->Update();
	}

	/**************************************
	���W�b�N�X�V����
	***************************************/
	void FieldController::UpdateLogic()
	{
		//�g��Ȃ��Ȃ������[�g�R���e�i���폜
		auto itr = std::remove_if(routeContainer.begin(), routeContainer.end(), [](auto& ptr)
		{
			return ptr->IsUnused();
		});
		routeContainer.erase(itr, routeContainer.end());

		for (auto&& route : routeContainer)
		{
			route->Update();
		}

		//AI���W���x�����v�Z
		CalcDevelopmentLevelAI();
	}

	/**************************************
	�`�揈��
	***************************************/
	void FieldController::Draw()
	{
		//ground->Draw();

		placeActController->Draw();

#ifdef DEBUG_PLACEMODEL
		operateContainer->DrawDebug();
		placeContainer->DrawDebug();
#endif
		//�J�[�\���ɂ͓��߃I�u�W�F�N�g���܂܂��̂ōŌ�ɕ`��
		cursor->Draw();
	}

	/**************************************
	CSV�ǂݍ��ݏ���
	TODO�F�ǂݍ��ރf�[�^��I���ł���悤�ɂ���
	***************************************/
	void FieldController::Load()
	{
		placeContainer->LoadCSV("data/FIELD/sample01.csv");

		//�A�N�^�[����
		auto places = placeContainer->GetAllPlaces();
		for (auto&& place : places)
		{
			placeActController->SetActor(place);
		}

		//�J�[�\���̃t�B�[���h�̒����֐ݒ�
		FieldPosition border = placeContainer->GetPlaceBorder();
		cursor->SetModelPosition(border.x / 2, border.z / 2);

		//NOTE:���͂܂��ړ��͈͂̊g�又���������̂ł����ňړ��͈͂����肵�Ă��܂�
		cursor->SetBorder(border.z - 1, border.x - 1, 0, 0);
	}

	/**************************************
	���͊m�F����
	***************************************/
	void FieldController::CheckInput()
	{
		input->CheckMoveInput();
	}

	/**************************************
	�J�[�\���擾����
	***************************************/
	GameObject * FieldController::GetFieldCursor()
	{
		return cursor;
	}

	/**************************************
	�r���[���p�����[�^���ߍ��ݏ���
	***************************************/
	void FieldController::EmbedViewerParam(GameViewerParam & param)
	{
		param.levelAI = (int)developmentLevelAI;
		param.ratioLevel = (float)developmentLevelAI / MaxDevelopmentLevelAI;
		developper->EmbedViewerParam(param);
	}

	/**************************************
	���쐬���̃f���Q�[�^�ݒ菈��
	***************************************/
	void FieldController::SetCallbackOnBuildRoad(Delegate<void(std::vector<Model::PlaceModel*>&)> *callback)
	{
		onBuildRoad = callback;
	}

	/**************************************
	���x���A�b�v���邩�ǂ����̔���
	***************************************/
	bool FieldController::ShouldLevelUp()
	{
		return developmentLevelAI >= MaxDevelopmentLevelAI;
	}

	/**************************************
	�C�x���g�n���h���쐬����
	***************************************/
	void FieldController::SetEventHandler(::FieldEventHandler& handler)
	{
		using Handler = ::FieldEventHandler;

		//AI���W���x�������t�@���N�^
		handler.functerFloat[Handler::FuncterID_float::AdjustAI] = [&](float percent)
		{
			float delta = developmentLevelAI * percent;
			developmentLevelAI = Math::Clamp(0.0f, 9999.0f, developmentLevelAI + delta);
		};

		//AI���W���x�����Z�t�@���N�^
		handler.functerFloat[Handler::FuncterID_float::AddAI] = [&](float num)
		{
			developmentLevelAI = Math::Clamp(0.0f, 9999.0f, developmentLevelAI + num);
		};

		//�S�̃����N���x�������t�@���N�^
		handler.functerInt[Handler::FuncterID_int::AdjustLinkAll] = [&](int num)
		{
			placeContainer->AddAllLinkLevel(num);
		};

		//�P�̃����N���x�������t�@���N�^
		handler.functerInt[Handler::FuncterID_int::AdjustLink] = [&](int num)
		{
			placeContainer->AddLinkLevel(num);
		};

		//�A�C�e���X�g�b�N���Z�t�@���N�^
		handler.functerInt[Handler::FuncterID_int::AddStock] = [&](int num)
		{
			developper->AddStock(num);
		};

		//���W�{���t�^�t�@���N�^
		handler.functerFloat[Handler::FuncterID_float::SetDevBonus] = [&](float percent)
		{
			developSpeedBonus = percent;
		};

		//�X�쐬�t�@���N�^
		handler.functerPlace[Handler::FuncterID_Place::Create] = [&](auto place)
		{
			//��ō��
		};

		//�X�j��t�@���N�^
		handler.functerPlace[Handler::FuncterID_Place::Destroy] = [&](auto place)
		{
			placeContainer->DestroyTown(place);
			placeActController->DestroyActor(place);
		};

		//���씽�]����
		handler.functerBool[Handler::FuncterID_bool::ReverseOpe] = [&](bool isReverse)
		{
			input->ReverseOperate(isReverse);
		};

		//�X�g�b�N���󏈗�
		handler.functerBool[Handler::FuncterID_bool::SealItem] = [&](bool isSeal)
		{
			//��ō��
		};

		//���G�x��������
		handler.functerFloat[Handler::FuncterID_float::AdjustTraffic] = [&](float bias)
		{
			placeContainer->SetTrafficjamBias(bias);
		};

		//EDF�X�g�b�N�g�p����
		handler.functerBoolReturn[Handler::FuncterID_boolReturn::TryEDF] = [&]()
		{
			return false;
		};

		//�ی��X�g�b�N�g�p����
		handler.functerBoolReturn[Handler::FuncterID_boolReturn::TryInsurance] = [&]()
		{
			return false;
		};

		//�j��Ώۂ̊X�擾����
		handler.functerPlaceReturn[Handler::FuncterID_PlaceReturn::DestroyTarget] = [&]()
		{
			return placeContainer->GetDestroyTarget();
		};

		//�X�쐬�\��n�̎擾����
		handler.functerPlaceReturn[Handler::FuncterID_PlaceReturn::PlacePosition] = [&]()
		{
			return placeContainer->GetNonePlace();
		};
	}

	/**************************************
	�X�e�[�g�؂�ւ�����
	***************************************/
	void FieldController::ChangeState(State next)
	{
		if (fsm[next] == NULL)
			return;

		current = next;
		state = fsm[next];
		state->OnStart(*this);
	}

	/**************************************
	�J�[�\���ʒu�̃v���C�X���擾
	***************************************/
	Model::PlaceModel * FieldController::GetPlace()
	{
		return placeContainer->GetPlace(cursor->GetModelPosition());
	}

	/**************************************
	AI���W���x���̌v�Z
	***************************************/
	void FieldController::CalcDevelopmentLevelAI()
	{
		cntFrame = Math::WrapAround((const int)0, DevelopmentInterval, cntFrame + 1);

		//���x���̏㏸��DevelopmentInterval�����ɍs��
		if (cntFrame != 0)
			return;

		float raiseValue = placeContainer->CalcDevelopmentLevelAI(developSpeedBonus);
		developmentLevelAI = Math::Clamp(0.0f, 9999.0f, developmentLevelAI + raiseValue);
	}
}