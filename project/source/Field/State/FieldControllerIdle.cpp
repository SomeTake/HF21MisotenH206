//=====================================
//
//�t�B�[���h�R���g���[���A�C�h����ԏ���[FieldControllerIdle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "FieldControllerIdle.h"
#include "../../../Framework/Input/input.h"
namespace Field
{
	/**************************************
	���ꏈ��
	***************************************/
	void FieldController::IdleState::OnStart(FieldController & entity)
	{

	}

	/**************************************
	�X�V����
	***************************************/
	FieldController::State FieldController::IdleState::OnUpdate(FieldController & entity)
	{
		return State::Idle;
	}

}