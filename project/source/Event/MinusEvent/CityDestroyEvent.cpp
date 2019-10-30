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
#include "../../../Framework/Task/TaskManager.h"

enum State
{
	TelopExpanding,
	MeteorDebut,
	BeatGameStart,
	BeatGameSuccess,
	BeatGameFail,
	EffectHappend,
};
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
#if _DEBUG
LPD3DXMESH CityDestroyEvent::SphereMesh = nullptr;
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
	EventState(State::TelopExpanding)
{
	// �A�ŃQ�[���C���X�^���X
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// �j�󂷂钬�̗\��n���擾
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(NegativeEvent01, [&]()
	{
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]() {MeteorFallStart(); });
	});

	// 覐Η��������v�Z
	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

#if _DEBUG
	// ���̃��b�V�����쐬����
	if (SphereMesh == nullptr)
	{
		LPDIRECT3DDEVICE9 Device = GetDevice();
		D3DXCreateSphere(Device, MeteoriteRadius, 16, 16, &SphereMesh, NULL);
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
	float Distance = 0.0f;

	switch (EventState)
	{
		// 覐Γo��
	case MeteorDebut:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

		if (Distance > pow(20.0f, 2))
		{
			MeteoritePos += MoveDirection * FallSpeed;
		}
		else
		{
			CountdownStart();
			EventState = State::BeatGameStart;
		}
		break;

	case BeatGameStart:

		// �A�ŃQ�[���̍X�V
		beatGame->Update();
		break;

		// 覐Ό��j
	case BeatGameSuccess:

		// 覐Ό��j�G�t�F�N�g
		GameParticleManager::Instance()->SetMissileHitEffect(MeteoritePos);
		// 30�t���[���̒x����ݒu
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			Camera::TranslationPlugin::Instance()->Restore(60, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
		break;

		// 覐Η���
	case BeatGameFail:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

		if (Distance > pow(3.0f, 2))
		{
			MeteoritePos += MoveDirection * FallSpeed;
		}
		else
		{
			// 覐Η����G�t�F�N�g
			GameParticleManager::Instance()->SetMeteorExplosionEffect(TownPos);
			// 30�t���[���̒x����ݒu
			TaskManager::Instance()->CreateDelayedTask(30, [&]()
			{
				Camera::TranslationPlugin::Instance()->Restore(60, [&]() { EventOver(); });
			});
			// �����ŏ���
			fieldEventHandler->DestroyTown(Target);
			EventState = EffectHappend;
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �`��
//=============================================================================
void CityDestroyEvent::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

#if _DEBUG
	if (EventState != State::EffectHappend)
	{
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
	}
#endif

	beatGame->Draw();
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
// �C�x���g�I������
//=============================================================================
void CityDestroyEvent::EventOver(void)
{
	// �C�x���g�I���A�Q�[�����s
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}

//=============================================================================
// �e���b�v�Đ��I���A覐Η����J�n
//=============================================================================
void CityDestroyEvent::MeteorFallStart(void)
{
	EventState = State::MeteorDebut;
}

//=============================================================================
// �A�ŃQ�[���̃J�E���g�_�E���J�n
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
	if (IsSuccess)
	{
		// �����A覐Ό��j
		EventState = State::BeatGameSuccess;
	}
	else
	{
		// ���s�A覐Η���
		EventState = State::BeatGameFail;
	}
}
