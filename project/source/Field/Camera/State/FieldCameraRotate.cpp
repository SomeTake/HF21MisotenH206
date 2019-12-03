//=====================================
//
//FieldCameraRotate.cpp
//�@�\:�t�B�[���h�J������]�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCameraRotate.h"
#include "../../../../Framework/Math/Easing.h"

/**************************************
���ꏈ��
***************************************/
void FieldCamera::FieldCameraRotate::OnStart(FieldCamera & entity)
{
	entity.startAngle = D3DXToRadian(entity.cameraAngle);
	entity.cameraAngle += entity.AnglePeriod;
	entity.endAngle = D3DXToRadian(entity.cameraAngle);

	if (entity.cameraAngle >= 360.0f)
	{
		entity.cameraAngle -= 360.0f;
		entity.startAngle -= D3DXToRadian(360.0f);
		entity.endAngle -= D3DXToRadian(360.0f);
	}

	entity.cntRotate = 0;
}

/**************************************
�X�V����
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraRotate::OnUpdate(FieldCamera & entity)
{
	entity.cntRotate++;

	float t = (float)entity.cntRotate / entity.DurationRotate;
	float angleXZ = Easing::EaseValue(t, entity.startAngle, entity.endAngle, EaseType::OutCubic);
	float angleY = D3DXToRadian(45.0f);

	D3DXVECTOR3 position = D3DXVECTOR3(
		cosf(angleY) * cosf(angleXZ),
		sinf(angleY),
		cosf(angleY) * sinf(angleXZ)) * 70.0f;

	D3DXVECTOR3 targetPosition = entity.targetObject->GetPosition();
	entity.transform->SetPosition(targetPosition + position);
	entity.transform->LookAt(targetPosition);

	return FieldCamera::AngleRotate;
}
