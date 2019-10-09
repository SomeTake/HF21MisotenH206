//=====================================
//
//�A�C�e���g�p����[UseItem.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "UseItem.h"
#include "../FieldInputController.h"
#include "../Place/OperatePlaceContainer.h"
#include "../Place/FieldPlaceContainer.h"
#include "../FieldCursor.h"

namespace Field
{
	/**************************************
	���ꏈ��
	***************************************/
	void FieldController::UseItemState::OnStart(FieldController & entity)
	{
		//���[�g�̊J�n�_���擾
		Model::PlaceModel* start = entity.GetPlace();

		//���[�g�̊J�n�����݂�
		bool result = entity.operateContainer->BeginDevelop(start);

		//�J�n�ł��Ȃ�������Idle��Ԃ֑J�ڂ���
		if (!result)
		{
			entity.ChangeState(State::Idle);
		}
	}

	/**************************************
	�X�V����
	***************************************/
	FieldController::State FieldController::UseItemState::OnUpdate(FieldController & entity)
	{
		//���̃X�e�[�g
		State next = State::Develop;

		//�J�[�\���ʒu�̃v���C�X�𑀍�ΏۂƂ��Ēǉ�
		Model::PlaceModel* place = entity.GetPlace();
		entity.operateContainer->AddDevelop(place);

		//X�L�[�������ꂽ�瑀��Ώۂ̃v���C�X�𓹂ɕς���
		//TODO�F�L�[�{�[�h�ȊO�̓��͂ɂ��Ή�
		if (GetDevelopTrigger())
		{
			if (entity.operateContainer->EndDevelop())
			{
				PlaceVector vector = entity.operateContainer->GetPlaces();
				entity.DevelopPlace(vector, vector.begin());
			}

			entity.operateContainer->Clear();

			next = State::Idle;
		}

		//Z�L�[�������ꂽ��Idle�X�e�[�g�֑J��
		if (GetDevelopCancel())
		{
			entity.operateContainer->Clear();
			next = State::Idle;
		}

		return next;
	}
}