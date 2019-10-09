//=====================================
//
//�t�B�[���h�̓��͊Ǘ�����[FieldInputController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "FieldInputController.h"
#include "../../Framework/Input/input.h"

namespace Field
{
	/**************************************
	�r���h�{�^���̃g���K�[���o
	***************************************/
	bool GetBuildTrigger()
	{
		if (Keyboard::GetTrigger(DIK_Z))
			return true;

		return false;
	}

	/**************************************
	�J��{�^���̃g���K�[���o
	***************************************/
	bool GetDevelopTrigger()
	{
		if (Keyboard::GetTrigger(DIK_X))
			return true;

		return false;
	}

	/**************************************
	�r���h�L�����Z�����o
	***************************************/
	bool GetBuildCancel()
	{
		//X�L�[�̃g���K�[���͂����o������L�����Z��
		if (Keyboard::GetTrigger(DIK_X))
			return true;

		return false;
	}

	/**************************************
	�J��L�����Z�����o
	***************************************/
	bool GetDevelopCancel()
	{
		//Z�L�[�̃g���K�[�����o������L�����Z��
		if (Keyboard::GetTrigger(DIK_Z))
			return true;

		return false;
	}
}


