//=====================================
//
//FieldCameraFar.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCameraFar.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
���ꏈ��
***************************************/
void FieldCamera::FieldCameraFar::OnStart(FieldCamera & entity)
{
	//�p�����[�^������
	entity.startPosition = entity.transform.GetPosition() - entity.targetObject->GetPosition();
	entity.cntFrame = 0;

	//�ړ���̍��W��ݒ�
	entity.goalPosition = D3DXVECTOR3(0.0f, 300.0f, 0.0f);
}

/**************************************
�X�V����
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraFar::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	//�C�[�W���O�ňړ�
	const float MoveDuration = 30;
	float t = entity.cntFrame / MoveDuration;
	D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::OutCubic);

	//�Ǐ]�ڕW�ɍ��킹�Ď��_��ݒ�
	entity.transform.SetPosition(position + entity.targetObject->GetPosition());

	return FieldCamera::FarView;
}
