//=====================================
//
//�t�B�[���h�̓��͊Ǘ�����[FieldInputController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "FieldInput.h"
#include "../../../Framework/Input/input.h"
#include "../Object/FieldCursor.h"

namespace Field
{
	/**************************************
	static�����o
	***************************************/
	const int FieldController::FieldInput::InputLongWait = 15;
	const int FieldController::FieldInput::InputShortWait = 3;

	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldController::FieldInput::FieldInput(FieldController * controller) :
		entity(controller),
		cntInputRepeat(0),
		directionInput(1)
	{

	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	FieldController::FieldInput::~FieldInput()
	{
	}

	/**************************************
	�r���h�{�^���̃g���K�[���o
	***************************************/
	bool FieldController::FieldInput::GetBuildTrigger()
	{
		if (Keyboard::GetTrigger(DIK_Z))
			return true;

		return false;
	}

	/**************************************
	�J��{�^���̃g���K�[���o
	***************************************/
	bool FieldController::FieldInput::GetDevelopTrigger()
	{
		if (Keyboard::GetTrigger(DIK_X))
			return true;

		return false;
	}

	/**************************************
	�r���h�L�����Z�����o
	***************************************/
	bool FieldController::FieldInput::GetBuildCancel()
	{
		//X�L�[�̃g���K�[���͂����o������L�����Z��
		if (Keyboard::GetTrigger(DIK_X))
			return true;

		return false;
	}

	/**************************************
	�J��L�����Z�����o
	***************************************/
	bool FieldController::FieldInput::GetDevelopCancel()
	{
		//Z�L�[�̃g���K�[�����o������L�����Z��
		if (Keyboard::GetTrigger(DIK_Z))
			return true;

		return false;
	}

	/**************************************
	�ړ����͊m�F
	***************************************/
	void FieldController::FieldInput::CheckMoveInput()
	{
		//�g���K�[�m�F
		float triggerX = 0.0f, triggerZ = 0.0f;

		triggerX = Input::GetTriggerHorizontal() * directionInput;
		triggerZ = -Input::GetTriggerVertical() * directionInput;

		//���s�[�g�m�F
		float repeatX = 0.0f, repeatZ = 0.0f;
		if ((Input::GetPressHorizontail() != 0.0f || Input::GetPressVertical() != 0.0f))
		{
			cntInputRepeat++;
			if (cntInputRepeat >= InputLongWait && cntInputRepeat % InputShortWait == 0)
			{
				repeatX = Input::GetPressHorizontail() * directionInput;
				repeatZ = -Input::GetPressVertical() * directionInput;
			}
		}
		else
		{
			cntInputRepeat = 0;
		}

		//�J�[�\�����ړ�
		float x = Math::Clamp(-1.0f, 1.0f, triggerX + repeatX);
		float z = Math::Clamp(-1.0f, 1.0f, triggerZ + repeatZ);
		entity->cursor->Move((int)x, (int)z);

		//���݂̃X�e�[�g�̍X�V���������s
		State next = entity->state->OnUpdate(*entity);
		if (next != entity->current)
		{
			entity->ChangeState(next);
		}
	}

	/**************************************
	���씽�]����
	***************************************/
	void FieldController::FieldInput::ReverseOperate(bool isReverse)
	{
		directionInput = isReverse ? -1 : 1;
	}
}


