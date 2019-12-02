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
#include "../../../../Framework/Tool/DebugWindow.h"

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
	entity.cameraAngle = -180.0f;
	const D3DXVECTOR3 startPosition = D3DXVECTOR3(0.0f, 200.0f, -100.0f);
	entity.startPosition = entity.transform->GetPosition();
	entity.cntFrame = 0;
	D3DXVECTOR3 vec = startPosition - Vector3::Zero;
	entity.distance = D3DXVec2Length(&D3DXVECTOR2(vec.x, vec.z));
	entity.transform->LookAt(targetPos);

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
	const int MoveDuration = 60;

	if (entity.cntFrame <= MoveDuration)
	{
		// �C�[�W���O�ňړ�
		float t = (float)entity.cntFrame / MoveDuration;
		D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition + targetPos, EaseType::InOutCirc);
		entity.transform->SetPosition(position);
		entity.transform->LookAt(targetPos);
	}
	else
	{
		// ��]��������
		entity.cameraAngle += 1.0f;
		if (entity.cameraAngle >= 180.0f)
		{
			entity.cameraAngle -= 360.0f;
		}
		D3DXVECTOR3 position = entity.transform->GetPosition() - targetPos;
		position.x = entity.distance * sinf(D3DXToRadian(entity.cameraAngle));
		position.z = entity.distance * cosf(D3DXToRadian(entity.cameraAngle));
		entity.transform->SetPosition(position + targetPos);
		entity.transform->LookAt(targetPos);
	}
	return FieldCamera::Arround;
}
