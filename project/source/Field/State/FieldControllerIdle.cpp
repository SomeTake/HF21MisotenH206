//=====================================
//
//�t�B�[���h�R���g���[���A�C�h����ԏ���[FieldControllerIdle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "FieldControllerIdle.h"
#include "../Controller/FieldInput.h"
#include "../Object/FieldCursor.h"

namespace Field
{
	/**************************************
	���ꏈ��
	***************************************/
	void FieldController::IdleState::OnStart(FieldController & entity)
	{
		//���ɉ������Ȃ�
	}

	/**************************************
	�X�V����
	***************************************/
	FieldController::State FieldController::IdleState::OnUpdate(FieldController & entity)
	{
		State next = State::Idle;

		//Z�L�[�������ꂽ��Build�֑J��
		if (entity.input->GetBuildTrigger())
		{
			entity.cursor->SetMode(FieldCursor::Mode::BuildRoad);
			next = State::Build;
		}

		//X�L�[�������ꂽ��Develop�֑J��
		if (entity.input->GetDevelopTrigger() && entity.enableDevelop)
		{
			entity.cursor->SetMode(FieldCursor::Mode::Develop);
			next = State::Develop;
		}

		return next;
	}

}