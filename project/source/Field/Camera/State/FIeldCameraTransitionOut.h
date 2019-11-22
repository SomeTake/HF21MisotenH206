//=====================================
//
//FieldCameraTransitionOut.h
//�@�\:���x���A�b�v�J�ڎ��̈����J�����X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCAMERATRANSITIONOUT_H_
#define _FIELDCAMERATRANSITIONOUT_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseState.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldCamera::FieldCameraTransitionOut : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);

	static const int DurationAccel;
	static const float MaxSpeed;
};

#endif