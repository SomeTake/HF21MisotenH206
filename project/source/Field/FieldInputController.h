//=====================================
//
// FieldInputController.h
// �@�\:�t�B�[���h�̓��͊Ǘ�
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDINPUTCONTROLLER_H_
#define _FIELDINPUTCONTROLLER_H_

#include "../../main.h"

namespace Field
{
	//���[�g���݊J�n�̓��͏���
	bool GetBuildTrigger();

	//�J��J�n�̓��͏���
	bool GetDevelopTrigger();

	//���[�g���݃L�����Z���̓��͏���
	bool GetBuildCancel();

	//�J��L�����Z���̓��͏���
	bool GetDevelopCancel();
}

#endif