//=====================================
//
//�t�B�[���h�R���g���[���A�C�h����ԏ���[FieldControllerIdle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "FieldControllerIdle.h"
#include "../FieldInputController.h"

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
		if (GetBuildTrigger())
		{
			next = State::Build;
		}

		//X�L�[�������ꂽ��Develop�֑J��
		if (GetDevelopTrigger())
		{
			next = State::Develop;
		}

		return next;
	}

}