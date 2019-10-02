//=====================================
//
//FieldCameraQuater.h
//�@�\:�t�B�[���h�J�����N�H�[�^�[�r���[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCAMERAQUATER_H_
#define _FIELDCAMERAQUATER_H_

#include "../../../main.h"
#include "FieldCamera.h"
#include "../../../Framework/Pattern/BaseState.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldCamera::FieldCameraQuater : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);
};
#endif