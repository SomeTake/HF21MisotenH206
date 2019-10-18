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

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../Event/EventController.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

#include <algorithm>

namespace Field
{
	/**************************************
	static�����o
	***************************************/
	const float FieldController::PlaceOffset = 10.0f;				//Place��1�}�X���̃I�t�Z�b�g�l
	const int FieldController::InitFieldBorder = 30;				//�t�B�[���h�͈͂̏����l
	const int FieldController::InputLongWait = 15;					//���̓��s�[�g�̑ҋ@�t���[��
	const int FieldController::InputShortWait = 5;					//���̓��s�[�g�̑ҋ@�t���[��
	const unsigned FieldController::InitDevelopRiverStock = 10;		//��J���X�g�b�N�̏�����
	const unsigned FieldController::InitDevelopMountainStock = 10;	//�R�J���X�g�b�N�̏�����
	const int FieldController::DevelopmentInterval = 30;			//���W���x���㏸�̃C���^�[�o��

	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder),
		inputRepeatCnt(0),
		cntFrame(0),
		developmentLevelAI(0),
		stockDevelopRiver(InitDevelopRiverStock),
		stockDevelopMountain(InitDevelopMountainStock),
		stockEDF(0),
		stockInsurance(0),
		developSpeedBonus(1.0f),
		onConnectTown(nullptr),
		onCreateJunction(nullptr),
		onChangePlaceType(nullptr)
	{
		//�C���X�^���X�쐬
		cursor = new FieldCursor(PlaceOffset);
		ground = new FieldGround();
		placeContainer = new Model::PlaceContainer();
		operateContainer = new Model::OperatePlaceContainer();
		placeActController = new Actor::PlaceActorController();

		//�X�e�[�g�}�V���쐬
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState();
		fsm[State::Develop] = new UseItemState();

		//�f���Q�[�g�쐬
		onConnectTown = Delegate<Model::PlaceContainer, const Model::PlaceModel*>::Create(placeContainer, &Model::PlaceContainer::OnConnectedTown);
		onCreateJunction = Delegate<Model::PlaceContainer, const Model::PlaceModel*>::Create(placeContainer, &Model::PlaceContainer::OnCreateJunction);
		onChangePlaceType = Delegate<Actor::PlaceActorController, const Model::PlaceModel*>::Create(placeActController, &Actor::PlaceActorController::ChangeActor);

		//���[�g�v���Z�b�T�쐬
		routeProcessor = new Model::RouteProcessor(onChangePlaceType);

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

		//�f���Q�[�g�폜
		SAFE_DELETE(onConnectTown);
		SAFE_DELETE(onCreateJunction);
		SAFE_DELETE(onChangePlaceType);

		//�X�e�[�g�}�V���폜
		Utility::DeleteContainer(fsm);
	}

	/**************************************
	�X�V����
	***************************************/
	void FieldController::Update()
	{
		//�g��Ȃ��Ȃ������[�g�R���e�i���폜
		auto itr = std::remove_if(routeContainer.begin(), routeContainer.end(), [](auto& ptr)
		{
			return ptr->IsUnused();
		});
		routeContainer.erase(itr, routeContainer.end());

		//�e�X�V����
		cursor->Update();
		placeContainer->Update();

		for (auto&& route : routeContainer)
		{
			route->Update();
		}

		placeActController->Update();

		//AI���W���x�����v�Z
		CalcDevelopmentLevelAI();

		Debug::Log("ControllerState:%d", current);
		Debug::Log("StockRiver:%d", stockDevelopRiver);
		Debug::Log("StockMountain:%d", stockDevelopMountain);
		Debug::Log("DevelopmentAILevel:%d", (int)developmentLevelAI);
	}

	/**************************************
	�`�揈��
	***************************************/
	void FieldController::Draw()
	{
		ground->Draw();

		placeActController->Draw();

#ifdef DEBUG_PLACEMODEL
		operateContainer->DrawDebug();
		placeContainer->DrawDebug();
#endif
		//�J�[�\���ɂ͓��߃I�u�W�F�N�g���܂܂��̂ōŌ�ɕ`��
		cursor->Draw();
	}

	/**************************************
	���͊m�F����
	TODO�F�ǂݍ��ރf�[�^��I���ł���悤�ɂ���
	***************************************/
	void FieldController::Load()
	{
		placeContainer->LoadCSV("data/FIELD/sample01.csv");

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
		//�g���K�[�m�F
		float triggerX = 0.0f, triggerZ = 0.0f;

		triggerX = Input::GetTriggerHorizontal();
		triggerZ = -Input::GetTriggerVertical();

		//���s�[�g�m�F
		float repeatX = 0.0f, repeatZ = 0.0f;
		if ((Input::GetPressHorizontail() != 0.0f || Input::GetPressVertical() != 0.0f))
		{
			inputRepeatCnt++;
			if (inputRepeatCnt >= InputLongWait && inputRepeatCnt % InputShortWait == 0)
			{
				repeatX = Input::GetPressHorizontail();
				repeatZ = -Input::GetPressVertical();
			}
		}
		else
		{
			inputRepeatCnt = 0;
		}

		//�J�[�\�����ړ�
		float x = Math::Clamp(-1.0f, 1.0f, triggerX + repeatX);
		float z = Math::Clamp(-1.0f, 1.0f, triggerZ + repeatZ);
		cursor->Move((int)x, (int)z);

		//���݂̃X�e�[�g�̍X�V���������s
		State next = state->OnUpdate(*this);
		if (next != current)
		{
			ChangeState(next);
		}
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
		param.ratioLevel = (float)developmentLevelAI / 9999.0f;
		param.stockBreakItem = stockDevelopMountain;
		param.stockBuildItem = stockDevelopRiver;
		param.stockEDF = stockEDF;
		param.stockInsurance = stockInsurance;
	}

	/**************************************
	AI���W���x���𑝂₷
	***************************************/
	void FieldController::AddLevelAI(float num)
	{
		float MaxLevel = 9999.0f;
		developmentLevelAI = Math::Clamp(0.0f, MaxLevel, developmentLevelAI + num);
	}

	/**************************************
	�X�̔��W���x���𑝂₷
	***************************************/
	void FieldController::AddLevelDevelopment(float num)
	{
		placeContainer->AddDevelopmentLevel(num);
	}

	/**************************************
	�X�g�b�N�A�C�e���̐��𑝂₷
	***************************************/
	void FieldController::AddStockItem(int num)
	{
		unsigned StockMax = 50;
		stockDevelopMountain = Math::Clamp((unsigned)0, StockMax, stockDevelopMountain + num);
		stockDevelopRiver = Math::Clamp((unsigned)0, StockMax, stockDevelopRiver + num);
	}

	/**************************************
	���W�X�s�[�h�ւ̃{�[�i�X�t�^
	***************************************/
	void FieldController::SetDevelopSpeedBonus()
	{
		//TODO ; ������������������
		//TODO : ���J�{���������ƌ��߂�
		developSpeedBonus = 1.5f;
	}

	/**************************************
	�V�����X���o��������
	***************************************/
	void FieldController::CreateNewTown()
	{
		//NOTE:��ō��
	}

	/**************************************
	�X��j�󂷂�
	***************************************/
	void FieldController::DestroyTown()
	{
		//NOTE�F��ō��
	}

	/**************************************
	����𔽓]������
	***************************************/
	void FieldController::ReverseOperation(bool isReverse)
	{
		//InputController������Ă���
	}

	/**************************************
	�X�g�b�N�A�C�e���g�p�𕕈󂷂�
	***************************************/
	void FieldController::SealUsingItem(bool isSeal)
	{
		//Developper������Ă���
	}

	/**************************************
	���G�x���㏸������
	***************************************/
	void FieldController::RaiseTrafficJam(float bias)
	{
		//TODO�F������������������
		placeContainer->SetTrafficjamBias(bias);
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
	�������
	***************************************/
	void FieldController::BuildRoad()
	{
		using namespace Field::Model;

		//����Ώۂ̃v���C�X��Road�^�C�v�ɕϊ�
		std::vector<PlaceModel*> route = operateContainer->GetPlaces();
		for (auto&& place : route)
		{
			if (place->IsType(PlaceType::None))
				place->SetType(PlaceType::Road);
		}

		//���[�g�x�N�g����n��
		EventController::CheckEventHappen(route, City);

		//���[�g���f���쐬
		RouteModelPtr ptr = RouteModel::Create(onConnectTown, onCreateJunction, route);

		//�[�_�ݒ�
		ptr->SetEdge();

		//�I�u�W�F�N�g�ݒ�

		//�אڂ��郋�[�g�ƘA��������
		routeProcessor->ConnectWithEdge(ptr, routeContainer);
		routeProcessor->Process(ptr, routeContainer);

		//����V����������̂ō��G�x���Čv�Z
		placeContainer->CaclTrafficJamRate();

		//�A�N�^�[����
		placeActController->SetActor(ptr);
	}

	/**************************************
	��A�R���J������
	***************************************/
	void FieldController::DevelopPlace(PlaceVector& route, PlaceIterator start)
	{
		using namespace Field::Model;

		auto head = std::find_if(start, route.end(), [](auto& place)
		{
			//��̊J�񏈗������Ă��Ȃ��̂ň�U�R�����g�A�E�g
			return place->IsType(PlaceType::Mountain) || place->IsType(PlaceType::River);
		});

		//�J��Ώۂ�������Ȃ��̂Ń��^�[��
		if (head == route.end())
			return;

		//�R���J��
		if ((*head)->IsType(PlaceType::Mountain))
		{
			head = DevelopMountain(route, head);
		}
		//����J��
		else if ((*head)->IsType(PlaceType::River))
		{
			head = DevelopRiver(route, head);
		}

		//�J�񂪏I�������ʒu����ċA�I�ɊJ��
		auto nextHead = std::find_if(head, route.end(), [](auto&& place)
		{
			return !place->IsDevelopableType();
		});

		DevelopPlace(route, nextHead);
	}

	/**************************************
	�R���J������
	***************************************/
	PlaceIterator FieldController::DevelopMountain(PlaceVector & route, PlaceIterator mountain)
	{
		using namespace Field::Model;

		//�Ώۂ̃v���C�X�̑O�ɂ���R,��ȊO�̃v���C�X��T��
		auto start = std::find_if(ReversePlaceIterator(mountain), route.rend(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//�R�ȊO��������Ȃ��������A��̏ꍇ�͑������^�[��
		if (start == route.rend() || (*(start + 1).base())->IsType(PlaceType::River))
		{
			return route.end();
		}

		//�Ώۂ̃v���C�X�̌��ɂ���R�A��ȊO�̃v���C�X��T��
		auto end = std::find_if(mountain, route.end(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//�R�ȊO��������Ȃ��������A��̏ꍇ�͑������^�[��
		if (end == route.end() || (*end)->IsType(PlaceType::River))
		{
			return route.end();
		}

		//start��end�����ԃv���C�X�̃R���e�i���쐬
		PlaceVector container;
		container.assign(start.base(), end);

		//�X�g�b�N������Ă���ΊJ��
		unsigned cntMountain = container.size();
		if (cntMountain <= stockDevelopMountain)
		{
			for (auto&& place : container)
			{
				place->SetType(PlaceType::None);
			}

			stockDevelopMountain -= cntMountain;
		}
		else
		{
			//�G���[���b�Z�[�W���Đ�
		}

		return end + 1;
	}

	/**************************************
	����J������
	***************************************/
	PlaceIterator FieldController::DevelopRiver(PlaceVector & route, PlaceIterator river)
	{
		using namespace Field::Model;

		//��̈�O�̃v���C�X�i�n�_�j���ǂ̕����ŗאڂ��Ă��邩�m�F
		PlaceModel* start = *(river - 1);
		Adjacency startAdjacency = (*river)->IsAdjacent(start);

		//�v���C�X��O�ֈ���m�F���Ă����I�_��T��
		PlaceIterator end = route.end();
		for (auto itr = river + 1; itr != route.end(); itr++)
		{
			PlaceModel* prev = *(itr - 1);
			PlaceModel* place = *itr;

			//�אڕ����������ɂȂ��Ă��Ȃ���Α������^�[��
			if (place->IsAdjacent(prev) != startAdjacency)
				return itr;

			//�J��\�ȊO�̃^�C�v�ł����break
			if (!place->IsDevelopableType())
			{
				end = itr;
				break;
			}
		}

		//�I�_��������Ȃ������̂ő������^�[��
		if (end == route.end())
			return route.end();

		//�n�_�ƏI�_�̊Ԃ̐�R���e�i���쐬
		PlaceVector riverVector;
		riverVector.assign(river, end);

		//�X�g�b�N������Ă���ΊJ��
		unsigned cntRiver = riverVector.size();
		if (cntRiver <= stockDevelopRiver)
		{
			Adjacency inverseStartAdjacency = GetInverseSide(startAdjacency);
			for (auto&& river : riverVector)
			{
				river->SetType(PlaceType::Bridge);
				river->AddDirection(startAdjacency);
				river->AddDirection(inverseStartAdjacency);
			}

			stockDevelopRiver -= cntRiver;
		}
		else
		{
			//�G���[���b�Z�[�W�̍Đ�
		}

		return end;
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
		AddLevelAI(raiseValue);
	}
}