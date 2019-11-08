//=============================================================================
//
// �����ŃC�x���g�N���X [CityDestroyEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "CityDestroyEvent.h"
#include "BeatGame.h"
#include "../EventActor/EventActorBase.h"
#include "../../Field/Place/FieldPlaceModel.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
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
// 覐΂̏����ʒu�Ɨ\��n�̋���
const float MeteoriteDistance = 200.0f;
// �������x
const float FallSpeed = 4.0f;
// 覐΃��f���̃X�P�[��
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CityDestroyEvent::CityDestroyEvent(EventViewer* eventViewer) :
	EventBase(true),
	EventState(State::TelopExpanding),
	eventViewer(eventViewer)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{
	SAFE_DELETE(Meteor);
	SAFE_DELETE(beatGame);
	eventViewer = nullptr;
}

//=============================================================================
// ������
//=============================================================================
void CityDestroyEvent::Init()
{
	// �A�ŃQ�[���C���X�^���X
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// �j�󂷂钬�̗\��n���擾
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// 覐Η��������v�Z
	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

	// 覐΃��b�V���쐬
	Meteor = new EventActorBase(MeteoritePos, Scale, "Meteor");

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::Meteorite, [&]()
	{
		CameraTranslationPlugin::Instance()->Move(TownPos, 30, [&]() {MeteorFallStart(); });
	});

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void CityDestroyEvent::Update()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

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
		GameParticleManager::Instance()->SetMeteorExplosionEffect(MeteoritePos);
		// 30�t���[���̒x����ݒu
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			CameraTranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
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
			// �����ŃG�t�F�N�g
			GameParticleManager::Instance()->SetTownExplosionEffect(TownPos);
			// 30�t���[���̒x����ݒu
			TaskManager::Instance()->CreateDelayedTask(30, [&]()
			{
				CameraTranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
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
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	if (EventState != State::EffectHappend)
	{
		Meteor->SetPosition(MeteoritePos);
		Meteor->Draw();
	}

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
