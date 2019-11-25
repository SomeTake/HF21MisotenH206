//=====================================
//
//FieldCameraTransitionOut.cpp
//�@�\:���x���A�b�v�J�ڎ��̈����J�����X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCameraTransitionOut.h"
#include "../../../../Framework/Math/Easing.h"

/**************************************
static�����o
***************************************/
const int FieldCamera::FieldCameraTransitionOut::DurationAccel = 30;
const float FieldCamera::FieldCameraTransitionOut::MaxSpeed = 8.0f;

/**************************************
���ꏈ��
***************************************/
void FieldCamera::FieldCameraTransitionOut::OnStart(FieldCamera & entity)
{
	//�p�����[�^������
	entity.cntFrame = 0;
}

/**************************************
�X�V��������
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraTransitionOut::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	float t = (float)entity.cntFrame / DurationAccel;
	float speed = Easing::EaseValue(t, 0.0f, MaxSpeed, EaseType::InOutCubic);
	entity.transform.Move(Vector3::Up * speed);

	entity.transform.LookAt(entity.targetObject->GetPosition());

	return FieldCamera::Mode::TransitionOut;
}
