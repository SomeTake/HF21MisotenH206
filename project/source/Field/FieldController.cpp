//=====================================
//
//FieldController.cpp
//�@�\:�t�B�[���h�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldController.h"
#include "Object/FieldCursor.h"
#include "Object/FieldSkyBox.h"
#include "Place\FieldPlaceContainer.h"
#include "Place\OperatePlaceContainer.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "Route\RouteProcessor.h"
#include "PlaceActorController.h"
#include "FieldEventHandler.h"
#include "Controller\FieldDevelopper.h"
#include "Controller\FieldInput.h"
#include "../FieldObject/InfoController.h"
#include "../Viewer/GameScene/Controller/FieldViewer.h"
#include "../Score/Score.h"

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Tool/ProfilerCPU.h"
#include "../../Framework/Math//Easing.h"
#include "../../Framework/Core/PlayerPrefs.h"
#include "../GameConfig.h"

#include <algorithm>

#include "../Effect/GameParticleManager.h"
#include "../../Framework/Math/Easing.h"
#include "../Reward/RewardController.h"

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
	FieldController::FieldController(Field::FieldLevel level) :
		fieldBorder(InitFieldBorder),
		cntFrame(0),
		developmentLevelAI(0),
		developSpeedBonus(1.0f),
		currentLevel(level),
		operationZ(OperationExplanationViewer::OperationID::Z_None),
		operationX(OperationExplanationViewer::OperationID::X_None),
		operationSpace(OperationExplanationViewer::OperationID::Space_None),
		enableDevelop(true),
		flgWaitPopup(false)
	{
		using Model::PlaceContainer;
		using Model::PlaceModel;

		//���\�[�X�ǂݍ���
		FieldSkyBox::LoadResource();
		Actor::PlaceActorController::LoadResource();

		//�C���X�^���X�쐬
		cursor = new FieldCursor(PlaceOffset);
		operateContainer = new Model::OperatePlaceContainer();
		developper = new FieldDevelopper(this);
		input = new FieldInput(this);
		placeContainer = new Model::PlaceContainer();
		viewer = new FieldViewer();
		score = new Score();

		//�t�B�[���h���x���ݒ�
		SetLevel(currentLevel);

		//�X�e�[�g�}�V���쐬
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState();
		fsm[State::Develop] = new UseItemState();

		//�t�@���N�^�쐬
		onConnectTown = std::bind(&FieldController::OnConnectedTown, this, std::placeholders::_1, std::placeholders::_2);
		onChangePlaceType = std::bind(&Actor::PlaceActorController::ChangeActor, placeActController, std::placeholders::_1);

		auto onDepartPassenger = std::bind(&Actor::PlaceActorController::DepartPassenger, placeActController, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		placeContainer->SetDepartPassengerFanctor(onDepartPassenger);

		auto onStartMorph = std::bind(&Actor::PlaceActorController::OnStartMorphing, placeActController, std::placeholders::_1, std::placeholders::_2);
		placeContainer->SetMorphingFantor(onStartMorph);

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
		SAFE_DELETE(skybox);
		SAFE_DELETE(cursor);
		SAFE_DELETE(placeContainer);
		SAFE_DELETE(operateContainer);
		SAFE_DELETE(routeProcessor);
		SAFE_DELETE(placeActController);
		SAFE_DELETE(developper);
		SAFE_DELETE(input);
		SAFE_DELETE(infoController);
		SAFE_DELETE(viewer);
		SAFE_DELETE(score);

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

		operateContainer->Update();

		placeActController->Update();

		infoController->Update();

		viewer->Update();

		//�f�o�b�O�c�[��
		Debug::Begin("DebugTool");
		if (Debug::Button("LinkUp 5"))
		{
			viewer->ViewLinkLevelUp(5);
		}
		Debug::SameLine();
		if (Debug::Button("LinkUp 15"))
		{
			viewer->ViewLinkLevelUp(15);
		}
		if (Debug::Button("Field Error"))
		{
			viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::NotConnection);
		}
		Debug::End();
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
		skybox->Draw();

		placeActController->Draw();

#ifdef DEBUG_PLACEMODEL
		placeContainer->DrawDebug();
#endif
		//�J�[�\���ɂ͓��߃I�u�W�F�N�g���܂܂��̂ōŌ�ɕ`��
		bool isSea = placeActController->IsOnSea(cursor->GetModelPosition());
		cursor->Draw(isSea);
		operateContainer->Draw();
	}

	/**************************************
	Info�`�揈��
	***************************************/
	void FieldController::DrawInfo()
	{
		infoController->Draw();
	}

	/**************************************
	UI�`�揈��
	***************************************/
	void FieldController::DrawViewer()
	{
		if (!isViewerActive)
			return;

		SetOperationExplanation();
		viewer->Draw();
	}

	/**************************************
	�t�B�[���h���x���ݒ菈��
	***************************************/
	void FieldController::SetLevel(Field::FieldLevel level)
	{
		LARGE_INTEGER start, end;

		currentLevel = level;

		//�t�B�[���h���x�����֌W����C���X�^���X���쐬
		start = ProfilerCPU::GetCounter();
		skybox = new FieldSkyBox(level);
		end = ProfilerCPU::GetCounter();

		Debug::Log("Create Skybox : %f", ProfilerCPU::CalcElapsed(start, end));


		placeActController = new Field::Actor::PlaceActorController(level);


		start = ProfilerCPU::GetCounter();
		infoController = new InfoController(level);
		end = ProfilerCPU::GetCounter();

		Debug::Log("Create InfoController : %f", ProfilerCPU::CalcElapsed(start, end));

		auto onDepartPassenger = std::bind(&Actor::PlaceActorController::DepartPassenger, placeActController, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		placeContainer->SetDepartPassengerFanctor(onDepartPassenger);

		auto onStartMorph = std::bind(&Actor::PlaceActorController::OnStartMorphing, placeActController, std::placeholders::_1, std::placeholders::_2);
		placeContainer->SetMorphingFantor(onStartMorph);

		onChangePlaceType = std::bind(&Actor::PlaceActorController::ChangeActor, placeActController, std::placeholders::_1);

		routeProcessor = new Model::RouteProcessor(onChangePlaceType);
	}

	/**************************************
	�N���A����
	***************************************/
	void FieldController::Clear()
	{
		//�t�B�[���h���x���Ɋ֌W�Ȃ����̂����Z�b�g
		cursor->Reset();
		operateContainer->Clear();
		placeContainer->Clear();
		routeContainer.clear();

		//�t�B�[���h���x�����֌W����C���X�^���X���폜
		SAFE_DELETE(skybox);
		SAFE_DELETE(placeActController);
		SAFE_DELETE(infoController);
		SAFE_DELETE(routeProcessor);

		//�p�����[�^���Z�b�g
		cntFrame = 0;
		developmentLevelAI = 0.0f;
		developSpeedBonus = 1.0f;
		enableDevelop = true;
		flgWaitPopup = false;

		//�X�e�[�g��Idle�֕ύX
		current = State::Idle;
		state = fsm[current];
	}

	/**************************************
	CSV�ǂݍ��ݏ���
	TODO�F�ǂݍ��ރf�[�^��I���ł���悤�ɂ���
	***************************************/
	void FieldController::Load()
	{
		LARGE_INTEGER start, end;

		//�A�N�^�[�̃f�[�^�ǂݍ���
		placeActController->Load();

		//���f���̃f�[�^�ǂݍ���
		start = ProfilerCPU::GetCounter();
		placeContainer->LoadCSV(Const::FieldDataFile[currentLevel]);
		end = ProfilerCPU::GetCounter();

		Debug::Log("Load ModelData : %f", ProfilerCPU::CalcElapsed(start, end));

		//�A�N�^�[����
		start = ProfilerCPU::GetCounter();
		auto places = placeContainer->GetAllPlaces();
		for (auto&& place : places)
		{
			placeActController->SetActor(place);
		}
		end = ProfilerCPU::GetCounter();

		Debug::Log("Create Actor : %f", ProfilerCPU::CalcElapsed(start, end));

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
		//param.levelAI = (int)developmentLevelAI;
		//param.ratioLevel = (float)developmentLevelAI / MaxDevelopmentLevelAI;
#if _DEBUG
		Debug::Begin("DebugTool");
		if (Debug::Button("AILevel 9999"))
			developmentLevelAI = 9999.0f;
		Debug::End();
#endif

		param.levelAI = (int)developmentLevelAI;
		param.ratioLevel = (float)developmentLevelAI / MaxDevelopmentLevelAI;
		param.currentFieldLevel = (int)currentLevel;
		developper->EmbedViewerParam(param);
	}

	/**************************************
	���쐬���̃R�[���o�b�N�ݒ菈��
	***************************************/
	void FieldController::SetCallbackBuildRoad(const std::function<void(std::vector<Model::PlaceModel*>&)>& callback)
	{
		onBuildRoad = callback;
	}

	/**************************************
	���x���A�b�v���邩�ǂ����̔���
	***************************************/
	bool FieldController::ShouldLevelUp()
	{
		//�F�����x���ł̓��x���A�b�v���Ȃ�
		if (currentLevel == FieldLevel::Space)
			return false;

		//AI���W���x�����ő�l�ɓ��B���Ă����烌�x���A�b�v����
		return developmentLevelAI >= MaxDevelopmentLevelAI;
	}

	/**************************************
	�J������؂�ւ��邩�ǂ����̔���
	***************************************/
	bool FieldController::ShouldSwicthCamera() const
	{
		return input->CheckSwicthCameraMode();
	}

	/**************************************
	�J��������]�����邩�ǂ����̔���
	***************************************/
	bool FieldController::ShouldRotateCamera() const
	{
		return input->CheckRotateCamera();
	}

	/*************************************
	�|�b�v�A�b�v��ҋ@���邩�ǂ���
	***************************************/
	bool FieldController::ShouldWaitPopup() const
	{
		return flgWaitPopup;
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
			SetLinkLevelInfo();
		};

		//�P�̃����N���x�������t�@���N�^
		handler.functerInt[Handler::FuncterID_int::AdjustLink] = [&](int num)
		{
			placeContainer->AddLinkLevel(num);
			SetLinkLevelInfo();
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
			placeContainer->CreateTown(place);
			placeActController->CreateNewTown(place);
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
			enableDevelop = !isSeal;
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

		//�A�g�����e�B�X�쐬�n�̎擾
		auto getAtlantis = std::bind(&FieldController::GetAtlantisPlace, this);
		handler.functerPlaceReturn[Handler::FuncterID_PlaceReturn::Atlantis] = getAtlantis;

		//�A�g�����e�B�X�o��
		handler.functerPlace[Handler::FuncterID_Place::SetAtlantis] = [&](auto place)
		{
			std::vector<const Model::PlaceModel*> container = placeContainer->CreateAtlantis(place);
			placeActController->SetAtlantis(place, container);
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
		float bonusSideWay = placeActController->GetSideWayBonus();

		//�F�����x���ł͍ő�l���Ƃ肠�������₵�Ă��܂�
		float MaxLevel = currentLevel == FieldLevel::Space ? MaxDevelopmentLevelAI * 1000.0f : MaxDevelopmentLevelAI;

		developmentLevelAI = Math::Clamp(0.0f, MaxLevel, developmentLevelAI + raiseValue + bonusSideWay);

		// �����[�h�ɔ��f
		if (currentLevel == FieldLevel::Space)
		{
			RewardController::Instance()->SetRewardData(RC::Type::MasterAI, (int)(developmentLevelAI));
		}
	}

	/**************************************
	�X���q������
	***************************************/
	void FieldController::OnConnectedTown(const Model::PlaceModel * town, const Model::PlaceModel * gate)
	{
		placeContainer->OnConnectedTown(town, gate);
		placeActController->OnConnectedTown(town);
	}

	/**************************************
	�A�g�����e�B�X�\��n�擾
	***************************************/
	const Model::PlaceModel * FieldController::GetAtlantisPlace()
	{
		std::vector<Model::PlaceModel*> ignoreList;

		while (true)
		{
			const Model::PlaceModel* target = placeContainer->GetNonePlace();

			if (placeActController->EnableAtlantis(target->GetPosition()))
				return target;

			ignoreList.push_back(const_cast<Model::PlaceModel*>(target));
		}

		return nullptr;
	}

	/**************************************
	�����N���x������InfoController�ɃZ�b�g����
	***************************************/
	void FieldController::SetLinkLevelInfo()
	{
		auto infoLinkLevel = placeContainer->GetAllTownLevel();
		infoController->SetAllLinkLevel(infoLinkLevel);
	}

	/**************************************
	��������̃Z�b�g
	***************************************/
	void FieldController::SetOperationExplanation()
	{
		viewer->SetOperationExplanation(
			(OperationExplanationViewer::OperationID)operationZ,
			(OperationExplanationViewer::OperationID)operationX,
			(OperationExplanationViewer::OperationID)operationSpace
		);
	}

	/**************************************
	UI�`��̉۔���Z�b�g
	***************************************/
	void FieldController::SetViewerActive(bool flag)
	{
		isViewerActive = flag;
	}

	/**************************************
	�X�R�A�̎擾
	***************************************/
	int FieldController::GetScore(FieldLevel current)
	{
		return score->GetScore(current);
	}

	/**************************************
	�X�R�A�̃Z�b�g
	***************************************/
	void FieldController::SetScore()
	{
		score->SetScore((int)developmentLevelAI, currentLevel);
	}
}