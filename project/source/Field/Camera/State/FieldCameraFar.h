//=====================================
//
//FieldCameraFar.h
//�@�\:�t�B�[���h�J�������i�r���[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCAMERAFAR_H_
#define _FIELDCAMERAFAR_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseState.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldCamera::FieldCameraFar : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);

	static const float CameraLength;
	static const float CameraAngleXZ;
	static const float CameraAngleY;
};
#endif