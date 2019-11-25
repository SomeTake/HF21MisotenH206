//=====================================
//
//FieldCameraTransitionIn.h
//�@�\:���x���A�b�v�J�ڎ��̃C���J�����X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCAMERATRANSITIONIN_H_
#define _FIELDCAMERATRANSITIONIN_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseState.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldCamera::FieldCameraTransitionIn : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);

	static const float CameraInitLength;
	static const float CameraGoalLength;
	static const float CameraAngleXZ;
	static const float CameraAngleY;
};

#endif