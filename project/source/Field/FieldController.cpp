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

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

#include <algorithm>

namespace Field
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder),
		inputRepeatCnt(0)
	{
		//�C���X�^���X�쐬
		cursor = new FieldCursor(PlaceOffset);
		ground = new FieldGround();
		placeContainer = new Model::PlaceContainer();
		operateContainer = new Model::OperatePlaceContainer();

		//�X�e�[�g�}�V���쐬
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState;
		fsm[State::Develop] = new UseItemState();

		//�X�e�[�g������
		ChangeState(State::Idle);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	FieldController::~FieldController()
	{
		routeContainer.clear();

		SAFE_DELETE(cursor);
		SAFE_DELETE(ground);
		SAFE_DELETE(placeContainer);
		SAFE_DELETE(operateContainer);

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
	}

	/**************************************
	�`�揈��
	***************************************/
	void FieldController::Draw()
	{
		ground->Draw();

		placeContainer->Draw();

		operateContainer->DrawDebug();

		//�J�[�\���ɂ͓��߃I�u�W�F�N�g���܂܂��̂ōŌ�ɕ`��
		cursor->Draw();

		Debug::Log("ControllerState:%d", current);
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
		triggerZ = Input::GetTriggerVertical();

		//���s�[�g�m�F
		float repeatX = 0.0f, repeatZ = 0.0f;
		if((Input::GetPressHorizontail() != 0.0f || Input::GetPressVertical() != 0.0f))
		{
			inputRepeatCnt++;
			if (inputRepeatCnt >= InputLongWait && inputRepeatCnt % InputShortWait == 0)
			{
				repeatX = Input::GetPressHorizontail();
				repeatZ = Input::GetPressVertical();
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

		//���[�g���f���쐬
		RouteModelPtr ptr = RouteModel::Create(route);
		routeContainer.push_back(ptr);
	
		//�[�_�ݒ�
		ptr->SetEdge();

		//�I�u�W�F�N�g�ݒ�

		//�אڂ��郋�[�g�ƘA��������
		RouteProcessor::ConnectWithEdge(ptr, routeContainer);
		RouteProcessor::Process(ptr, routeContainer);
	}

	/**************************************
	��A�R���J������
	***************************************/
	void FieldController::DevelopPlace(PlaceVector& route, PlaceIterator start)
	{
		using namespace Field::Model;

		auto itr = std::find_if(start, route.end(), [](auto& place)
		{
			//��̊J�񏈗������Ă��Ȃ��̂ň�U�R�����g�A�E�g
			//return place->IsType(PlaceType::Mountain) || place->IsType(PlaceType::River);
			return place->IsType(PlaceType::Mountain);
		});

		//�J��Ώۂ�������Ȃ��̂Ń��^�[��
		if (itr == route.end())
			return;

		//�R���J��
		if ((*itr)->IsType(PlaceType::Mountain))
		{
			itr = DevelopMountain(route, itr);
		}

		//�J�񂪏I�������ʒu����ċA�I�ɊJ��
		DevelopPlace(route, itr);
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

		//start��end�����ԃv���C�X���J�񂷂�
		PlaceVector container;
		container.assign(start.base(), end);
		for (auto&& place : container)
		{
			place->SetType(PlaceType::None);
		}

		return end + 1;
	}
}