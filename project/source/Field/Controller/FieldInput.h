//=====================================
//
// FieldInputController.h
// �@�\:�t�B�[���h�̓��͊Ǘ�
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDINPUTCONTROLLER_H_
#define _FIELDINPUTCONTROLLER_H_

#include "../../../main.h"
#include "../FieldController.h"

namespace Field
{
	/**************************************
	FieldInput�N���X
	***************************************/
	class FieldController::FieldInput
	{
	public :
		FieldInput(FieldController *controller);
		~FieldInput();

		//���[�g���݊J�n�̓��͏���
		bool GetBuildTrigger();

		//�J��J�n�̓��͏���
		bool GetDevelopTrigger();

		//���[�g���݃L�����Z���̓��͏���
		bool GetBuildCancel();

		//�J��L�����Z���̓��͏���
		bool GetDevelopCancel();

		//�ړ����͊m�F
		void CheckMoveInput();

		//�J�����̓��͐؂�ւ�
		bool CheckSwicthCameraMode();

		//���씽�]����
		void ReverseOperate(bool isReverse);

	private:
		FieldController * entity;

		static const int InputLongWait;
		static const int InputShortWait;
		
		int cntInputRepeat;

		int directionInput;
	};
}

#endif