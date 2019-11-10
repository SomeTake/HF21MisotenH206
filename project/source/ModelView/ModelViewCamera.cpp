//=====================================
//
//���f���r���[�J��������[ModelViewCamera.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ModelViewCamera.h"
#include "../../Framework/Input/input.h"

/**************************************
�R���X�g���N�^
***************************************/
ModelViewCamera::ModelViewCamera()
{
	//�p�����[�^�ݒ�
	const float CameraAngleXZ = D3DXToRadian(45.0f);
	const float CameraAngleY = D3DXToRadian(45.0f);
	const float CameraLength = 70.0f;

	const D3DXVECTOR3 InitPos = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	transform.SetPosition(InitPos);
}

/**************************************
�X�V����
***************************************/
void ModelViewCamera::Update()
{
	const float MoveSpeed = 2.0f;

	if (Keyboard::GetPress(DIK_LEFT))
	{
		transform.Move(Vector3::Left * MoveSpeed);
		transform.LookAt(transform.GetPosition() + Vector3::Down);
	}
	if (Keyboard::GetPress(DIK_RIGHT))
	{
		transform.Move(Vector3::Right * MoveSpeed);
		transform.LookAt(transform.GetPosition() + Vector3::Down);
	}
	if (Keyboard::GetPress(DIK_UP))
	{
		transform.Move(Vector3::Forward * MoveSpeed);
		transform.LookAt(transform.GetPosition() + Vector3::Down);
	}
	if (Keyboard::GetPress(DIK_DOWN))
	{
		transform.Move(Vector3::Back * MoveSpeed);
		transform.LookAt(transform.GetPosition() + Vector3::Down);
	}

	Camera::Update();
}
