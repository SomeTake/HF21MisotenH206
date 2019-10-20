//=============================================================================
//
// �����ŃC�x���g�N���X [CityDestroyEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "CityDestroyEvent.h"
#include "../EventConfig.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// 覐΂̔��a
const float MeteoriteRadius = 3.0f;
const float MeteoriteDistance = 200.0f;
const float FallSpeed = 4.0f;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
LPDIRECT3DDEVICE9 CityDestroyEvent::Device = nullptr;
LPD3DXMESH CityDestroyEvent::SphereMesh = nullptr;
D3DMATERIAL9 CityDestroyEvent::Material =
{
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// Diffuse color RGBA
	D3DXCOLOR(1.0f, 0.65f, 0.0f, 1.0f),	// Ambient color RGB
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Specular 'shininess'
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Emissive color RGB
	0.0f,								// Sharpness if specular highlight 
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CityDestroyEvent::CityDestroyEvent(D3DXVECTOR3 GoalPos) : GoalPos(GoalPos)
{
	Pos = GoalPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	FallDirection = GoalPos - Pos;
	D3DXVec3Normalize(&FallDirection, &FallDirection);

	// �f�o�C�X�擾
	if (Device == nullptr)
	{
		Device = GetDevice();
	}

	// ���̃��b�V�����쐬����
	if (SphereMesh == nullptr)
	{
		D3DXCreateSphere(Device, MeteoriteRadius, 16, 16, &SphereMesh, NULL);
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void CityDestroyEvent::Update()
{
	float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(GoalPos - Pos));

	if (Distance > pow(3.0f, 2))
	{
		Pos += FallDirection * FallSpeed;
	}
	else
	{
		fieldController->DestroyTown();
		this->UseFlag = false;
	}
}

//=============================================================================
// �`��
//=============================================================================
void CityDestroyEvent::Draw()
{
	D3DXMATRIX WorldMatrix, TransMatrix;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMatrix);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&TransMatrix, Pos.x, Pos.y, Pos.z);
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

	// ���[���h�}�g���b�N�X�̐ݒ�
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// �}�e���A���̐ݒ�
	Device->SetMaterial(&Material);

	// ���̕`��
	SphereMesh->DrawSubset(0);
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string CityDestroyEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("���̒��͕����΂ɂ��悤");
	}
	else if (FieldLevel == Field::Model::World)
	{

	}
	else if (FieldLevel == Field::Model::Space)
	{

	}

	if (!MessageContainer.empty())
	{
		int MessageNo = rand() % MessageContainer.size();
		return MessageContainer.at(MessageNo);
	}
	else
	{
		string ErrMsg = "�C�x���g���b�Z�[�W������܂���";
		return ErrMsg;
	}
}
