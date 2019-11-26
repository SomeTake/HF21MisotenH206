//=====================================
//
// �t�B�[���h�J�����A���E���h[FieldCameraArround.cpp]
// �@�\�F�t�B�[���h�̒��S���œ_�ɂ��ĉ�]����J�����i�^�C�g���A���U���g�p�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "FieldCameraArround.h"
#include "../../FieldConfig.h"
#include "../../../../Framework/Math/Easing.h"

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************

//=====================================
// ����
//=====================================
void FieldCamera::FieldCameraArround::OnStart(FieldCamera & entity)
{
	// �p�����[�^������
	const D3DXVECTOR3 targetPos = Field::FieldPosition(25, 25).ConvertToWorldPosition();
	const D3DXVECTOR3 startPosition = D3DXVECTOR3(250.0f, 300.0f, -400.0f);
	entity.startPosition = entity.transform.GetPosition();
	entity.cntFrame = 0;
	entity.cameraAngle = 180.0f;
	entity.transform.LookAt(targetPos);

	// �ړ���
	entity.goalPosition = startPosition;
}

//=====================================
// �X�V
//=====================================
FieldCamera::Mode FieldCamera::FieldCameraArround::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	D3DXVECTOR3 targetPos = Field::FieldPosition(25, 25).ConvertToWorldPosition();
	D3DXVECTOR3 vec = targetPos - entity.goalPosition;
	const float Dist = D3DXVec3Length(&vec);
	const int MoveDuration = 60;

	if (entity.cntFrame <= MoveDuration)
	{
		// �C�[�W���O�ňړ�
		float t = (float)entity.cntFrame / MoveDuration;
		D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::InOutCirc);
		entity.transform.SetPosition(position);
		entity.transform.LookAt(targetPos);
	}
	else
	{
		// ��]��������
		entity.cameraAngle += 1.5f;
		if (entity.cameraAngle >= 180.0f)
		{
			entity.cameraAngle -= 360.0f;
		}
		D3DXVECTOR3 position = entity.transform.GetPosition() + entity.targetObject->GetPosition();
		position.x = Dist * sinf(D3DXToRadian(entity.cameraAngle));
		position.z = Dist * cosf(D3DXToRadian(entity.cameraAngle));
		entity.transform.SetPosition(position + targetPos);
		entity.transform.LookAt(targetPos);
	}

	return FieldCamera::Arround;
}
