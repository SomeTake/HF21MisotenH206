//=====================================
//
//FieldCameraRotate.h
//�@�\:�t�B�[���h�J������]�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCAMEARAROTATE_H_
#define _FIELDCAMEARAROTATE_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../FieldCamera.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldCamera::FieldCameraRotate : public BaseState<FieldCamera, Mode>
{
public:
	void OnStart(FieldCamera& entity);
	Mode OnUpdate(FieldCamera& entity);
};
#endif