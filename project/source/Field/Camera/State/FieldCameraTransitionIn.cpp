//=====================================
//
//FieldCameraTransitionIn.cpp
//�@�\:���x���A�b�v�J�ڎ��̃C���J�����X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCameraTransitionIn.h"
#include "../../../../Framework/Math/Easing.h"

/**************************************
static�����o
***************************************/
const float FieldCamera::FieldCameraTransitionIn::CameraInitLength = 10.0f;
const float FieldCamera::FieldCameraTransitionIn::CameraGoalLength = 200.0f;
const float FieldCamera::FieldCameraTransitionIn::CameraAngleXZ = D3DXToRadian(45.0f);
const float FieldCamera::FieldCameraTransitionIn::CameraAngleY = D3DXToRadian(85.0f);

/**************************************
���ꏈ��
***************************************/
void FieldCamera::FieldCameraTransitionIn::OnStart(FieldCamera & entity)
{
	//�p�����[�^������
	entity.cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraTransitionIn::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	const int MoveDuration = 90;
	float t = (float)entity.cntFrame / MoveDuration;

	float length = Easing::EaseValue(t, CameraInitLength, CameraGoalLength, EaseType::InOutCubic);

	D3DXVECTOR3 offset = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * length;

	D3DXVECTOR3 targetPosition = entity.targetObject->GetPosition();

	entity.transform->SetPosition(targetPosition + offset);
	entity.transform->LookAt(targetPosition);

	return FieldCamera::Mode::TransitionIn;
}
