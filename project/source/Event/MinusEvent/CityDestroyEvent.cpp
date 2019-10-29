//=============================================================================
//
// �����ŃC�x���g�N���X [CityDestroyEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "CityDestroyEvent.h"
#include "BeatGame.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../Effect/GameParticleManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// 覐΂̔��a
const float MeteoriteRadius = 3.0f;
const float MeteoriteDistance = 200.0f;
const float FallSpeed = 4.0f;
// 覐΂�����܂ł̎���
const int EscapeTime = 10;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
#if _DEBUG
LPD3DXMESH CityDestroyEvent::SphereMesh = nullptr;
LPD3DXMESH CityDestroyEvent::MissileMesh = nullptr;
D3DMATERIAL9 CityDestroyEvent::Material =
{
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// Diffuse color RGBA
	D3DXCOLOR(1.0f, 0.65f, 0.0f, 1.0f),	// Ambient color RGB
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Specular 'shininess'
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Emissive color RGB
	0.0f,								// Sharpness if specular highlight 
};
#endif

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CityDestroyEvent::CityDestroyEvent(EventViewer* eventViewer) :
	EventAvoid(false),
	BeatGameOver(false)
{
	// �A�ŃQ�[���C���X�^���X
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// �j�󂷂钬�̗\��n���擾
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();
	MissilePos = TownPos;

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(NegativeEvent01, [&]()
	{
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]()
		{
			CountdownStart();
		});
	});

	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

#if _DEBUG
	// ���̃��b�V�����쐬����
	if (SphereMesh == nullptr)
	{
		LPDIRECT3DDEVICE9 Device = GetDevice();
		D3DXCreateSphere(Device, MeteoriteRadius, 16, 16, &SphereMesh, NULL);
		D3DXCreateSphere(Device, 1.0f, 16, 16, &MissileMesh, NULL);
	}
#endif
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{
	SAFE_DELETE(beatGame);
}

//=============================================================================
// �X�V
//=============================================================================
void CityDestroyEvent::Update()
{
	if (!BeatGameOver)
	{
		beatGame->Update();
	}
	else
	{
		if (EventAvoid)
		{
			// =================
			// �~�T�C������
			// =================
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - MissilePos));

			if (Distance > pow(3.0f, 2))
			{
				MissilePos += MoveDirection * FallSpeed;
				MeteoritePos += -MoveDirection * FallSpeed;
				Camera::TranslationPlugin::Instance()->Move(MissilePos, 1, nullptr);
			}
			else
			{
				// �~�T�C�������G�t�F�N�g
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				this->UseFlag = false;
			}
		}
		else
		{
			// =================
			// 覐Η���
			// =================
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

			if (Distance > pow(3.0f, 2))
			{
				MeteoritePos += MoveDirection * FallSpeed;
			}
			else
			{
				// 覐Η����G�t�F�N�g
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				// �����ŏ���
				fieldEventHandler->DestroyTown(Target);
				this->UseFlag = false;
			}
		}
	}

	if (!UseFlag)
	{
		// �C�x���g�I���A�Q�[�����s
		fieldEventHandler->ResumeGame();
	}
}

//=============================================================================
// �`��
//=============================================================================
void CityDestroyEvent::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	beatGame->Draw();

#if _DEBUG
	D3DXMATRIX WorldMatrix, TransMatrix;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMatrix);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&TransMatrix, MeteoritePos.x, MeteoritePos.y, MeteoritePos.z);
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

	// ���[���h�}�g���b�N�X�̐ݒ�
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// �}�e���A���̐ݒ�
	Device->SetMaterial(&Material);

	// ���̕`��
	SphereMesh->DrawSubset(0);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMatrix);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&TransMatrix, MissilePos.x, MissilePos.y, MissilePos.z);
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

	// ���[���h�}�g���b�N�X�̐ݒ�
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// �~�T�C���`��
	MissileMesh->DrawSubset(0);
#endif
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string CityDestroyEvent::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}


//=============================================================================
// 覐΂�����܂ł̃J�E���g�_�E��
//=============================================================================
void CityDestroyEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
}

//=============================================================================
// �A�ŃQ�[���̌��ʂɂ�鏈��
//=============================================================================
void CityDestroyEvent::ReceiveBeatResult(bool IsSuccess)
{
	BeatGameOver = true;

	if (IsSuccess)
	{
		// �����A�~�T�C������
		EventAvoid = true;
		MoveDirection = D3DXVECTOR3(MeteoritePos - MissilePos);
		D3DXVec3Normalize(&MoveDirection, &MoveDirection);
	}
	else
	{
		// ���s�A覐Η���
		EventAvoid = false;
	}
}
