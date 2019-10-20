//=====================================
//
//FieldCameraQuater.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCameraQuater.h"
#include "../../../../Framework/Math/Easing.h"

/**************************************
���ꏈ��
***************************************/
void FieldCamera::FieldCameraQuater::OnStart(FieldCamera & entity)
{
	//�p�����[�^������
	entity.startPosition = entity.transform.GetPosition() - entity.targetObject->GetPosition();
	entity.cntFrame = 0;


	//�ړ���̍��W��ݒ�
	const float CameraAngleXZ = D3DXToRadian(45.0f);
	const float CameraAngleY = D3DXToRadian(60.0f);
	const float CameraLength = 50.0f;

	entity.goalPosition = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	entity.transform.SetRotation(D3DXVECTOR3(CameraAngleY, CameraAngleXZ, 0.0f));
}

/**************************************
�X�V����
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraQuater::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	//�C�[�W���O�ňړ�
	const float MoveDuration = 30;
	float t = entity.cntFrame / MoveDuration;
	D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::OutCubic);

	//�Ǐ]�ڕW�ɍ��킹�Ď��_��ݒ�
	entity.transform.SetPosition(position + entity.targetObject->GetPosition());

	return FieldCamera::QuaterView;
}