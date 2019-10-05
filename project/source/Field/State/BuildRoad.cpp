//=====================================
//
//�e���v���[�g����[BuildRoad.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BuildRoad.h"
#include "../../../Framework/Input/input.h"
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
		bool result = entity.operateContainer->Begin(start);

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
		entity.operateContainer->Add(place);

		//Z�L�[�������ꂽ�瑀��Ώۂ̃v���C�X�𓹂ɕς���
		//TODO�F�L�[�{�[�h�ȊO�̓��͂ɂ��Ή�
		if (Keyboard::GetTrigger(DIK_Z))
		{
			if (entity.operateContainer->End())
			{
				entity.BuildRoad();
			}

			entity.operateContainer->Clear();

			next = State::Idle;
		}

		//X�L�[�������ꂽ��Idle�X�e�[�g�֑J��
		if (Keyboard::GetTrigger(DIK_X))
		{
			next = State::Idle;
		}

		return next;
	}

}