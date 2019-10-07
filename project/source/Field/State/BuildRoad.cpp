//=====================================
//
//�e���v���[�g����[BuildRoad.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BuildRoad.h"
#include "../FieldInputController.h"
#include "../Place/OperatePlaceContainer.h"
#include "../Place/FieldPlaceContainer.h"
#include "../FieldCursor.h"

namespace Field
{
	/**************************************
	���ꏈ��
	***************************************/
	void FieldController::BuildRoadState::OnStart(FieldController & entity)
	{
		//���[�g�̊J�n�_���擾
		Model::PlaceModel* start = entity.GetPlace();

		//���[�g�̊J�n�����݂�
		bool result = entity.operateContainer->BeginRoute(start);

		//�J�n�ł��Ȃ�������Idle��Ԃ֑J�ڂ���
		if (!result)
		{
			entity.ChangeState(State::Idle);
		}
	}

	/**************************************
	���ꏈ��
	***************************************/
	FieldController::State FieldController::BuildRoadState::OnUpdate(FieldController & entity)
	{
		//���̃X�e�[�g
		State next = State::Build;

		//�J�[�\���ʒu�̃v���C�X�𑀍�ΏۂƂ��Ēǉ�
		Model::PlaceModel* place = entity.GetPlace();
		entity.operateContainer->AddRoute(place);

		//Z�L�[�������ꂽ�瑀��Ώۂ̃v���C�X�𓹂ɕς���
		//TODO�F�L�[�{�[�h�ȊO�̓��͂ɂ��Ή�
		if (GetBuildTrigger())
		{
			if (entity.operateContainer->EndRoute())
			{
				entity.BuildRoad();
			}

			entity.operateContainer->Clear();

			next = State::Idle;
		}

		//X�L�[�������ꂽ��Idle�X�e�[�g�֑J��
		if (GetBuildCancel())
		{
			entity.operateContainer->Clear();
			next = State::Idle;
		}

		return next;
	}

}