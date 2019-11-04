//=====================================
//
//FieldCameraFar.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCameraFar.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Input/input.h"

/**************************************
static�����o
***************************************/
const float FieldCamera::FieldCameraFar::CameraLength = 200.0f;
const float FieldCamera::FieldCameraFar::CameraAngleXZ = D3DXToRadian(90.0f);
const float FieldCamera::FieldCameraFar::CameraAngleY = D3DXToRadian(85.0f);

/**************************************
���ꏈ��
***************************************/
void FieldCamera::FieldCameraFar::OnStart(FieldCamera & entity)
{
	//�p�����[�^������
	entity.startPosition = entity.transform.GetPosition() - entity.targetObject->GetPosition();
	entity.cntFrame = 0;

	//�ړ���̍��W��ݒ�
	entity.goalPosition = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;
}

/**************************************
�X�V����
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraFar::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	const float MoveDuration = 30;
	if (entity.cntFrame <= MoveDuration)
	{
		//�C�[�W���O�ňړ�
		float t = entity.cntFrame / MoveDuration;
		D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::OutCubic);

		//�Ǐ]�ڕW�ɍ��킹�Ď��_��ݒ�
		entity.transform.SetPosition(position + entity.targetObject->GetPosition());
	}
	else
	{
		//����ňړ�
		const float MoveSpeed = 3.0f;

		D3DXVECTOR3 directionMove = {
			Input::GetPressHorizontail(),
			0.0f,
			Input::GetPressVertical()
		};

		D3DXVec3Normalize(&directionMove, &directionMove);

		D3DXVECTOR3 position = entity.target;
		position += directionMove * MoveSpeed;
		position.x = Math::Clamp(0.0f, 50 * 10.0f, position.x);
		position.z = Math::Clamp(-50 * 10.0f, 0.0f, position.z);

		entity.target = position;

		D3DXVECTOR3 eyePosition = D3DXVECTOR3(
			cosf(CameraAngleY) * cosf(CameraAngleXZ),
			sinf(CameraAngleY),
			cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

		entity.transform.SetPosition(position + eyePosition);
	}

	return FieldCamera::FarView;
}
