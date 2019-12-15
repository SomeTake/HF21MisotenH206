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
#include "../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Field/Camera/EventCamera.h"
#include "../../Viewer/GameScene/GuideViewer/GuideActor.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"
#include "../../Sound/PlayBGM.h"
#include "../../Booth/BoothController.h"

enum State
{
	TelopExpanding,
	MeteorDebut,
	CameraMoveWait,
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
CityDestroyEvent::CityDestroyEvent(EventViewer* eventViewer, BeatGameViewer* beatViewer, EventCamera* camera) :
	EventBase(true),
	EventState(State::TelopExpanding),
	eventViewer(eventViewer),
	camera(camera),
	beatViewer(beatViewer),
	success(false)
{
	PlayBGM::Instance()->Pause();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{
	SAFE_DELETE(Meteor);
	SAFE_DELETE(beatGame);
	SAFE_DELETE(guideActor);
	eventViewer = nullptr;
}

//=============================================================================
// ������
//=============================================================================
void CityDestroyEvent::Init()
{
	//�J�������C�x���g�J�����ɐ؂�ւ�
	camera->Init();

	// �A�ŃQ�[���C���X�^���X
	auto onFinishBeat = std::bind(&CityDestroyEvent::OnFinisheBeat, this, std::placeholders::_1);
	beatGame = new BeatGame(BeatGame::CityDestroyEvent, beatViewer, [&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); }, onFinishBeat);

	// �j�󂷂钬�̗\��n���擾
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// 覐Η��������v�Z
	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

	// 覐΃��b�V���쐬
	Meteor = new EventActorBase(MeteoritePos, Scale, "Meteor");

	//�K�C�h�L�����쐬
	guideActor = new GuideActor();
	guideActor->SetActive(false);
	guideActor->SetScale(Vector3::One * 0.05f);

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::Meteorite, [&]()
	{
		PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::DestroyEvent, 0.1f, 30);
		camera->Translation(TownPos, 30, [&]() {MeteorFallStart(); });
	});

	//�u�[�X��LED��_�ł�����
	BoothController::Instance()->BlinkLED(false);

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
	D3DXVECTOR3 diff = Vector3::Zero;

	switch (EventState)
	{
		// 覐Γo��
	case MeteorDebut:

		diff = TownPos - MeteoritePos;
		Distance = D3DXVec3LengthSq(&diff);

		if (Distance > pow(40.0f, 2))
		{
			MeteoritePos += MoveDirection * FallSpeed;
		}
		else
		{
			EventState = CameraMoveWait;

			//�K�C�h�L�������A�N�e�B�x�C�g���Ĉړ�
			guideActor->SetActive(true);
			
			D3DXVECTOR3 guidePos = Vector3::Normalize(diff) * 7.5f + MeteoritePos;
			guideActor->SetPosition(TownPos);
			guideActor->Move(guidePos, 60);

			guideActor->LookAt(MeteoritePos);

			guideActor->ChangeAnim(GuideActor::AnimState::FightingIdle, true);

			//�J�����̈ړ�
			D3DXVECTOR3 nextCameraPos = Vector3::Normalize(diff) * 25.0f + MeteoritePos + Vector3::Back * 10.0f;
			camera->Move(nextCameraPos, 30, 35.0f, [this]
			{
				CountdownStart();
			});
		}
		break;

	case BeatGameStart:

		// �A�ŃQ�[���̍X�V
		beatGame->Update();
		break;

		// 覐Ό��j
	case BeatGameSuccess:

		PlayBGM::Instance()->FadeOut();
		// 覐Ό��j�G�t�F�N�g
		GameParticleManager::Instance()->SetMeteorExplosionEffect(MeteoritePos);
		// 30�t���[���̒x����ݒu
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			guideActor->SetActive(false);
			camera->Return(30, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
		break;

		// 覐Η���
	case BeatGameFail:

		PlayBGM::Instance()->FadeOut();
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
				camera->Return(30, [&]() { EventOver(); });
			});
			// �����ŏ���
			fieldEventHandler->DestroyTown(Target);
			EventState = EffectHappend;
		}
		break;

	default:
		break;
	}

	if (guideActor->IsActive())
		guideActor->Update();
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

	if (guideActor->IsActive())
		guideActor->Draw();

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
	camera->Restore();
	fieldEventHandler->ResumeGame();
	UseFlag = false;

	// �C�x���g�̉ۂɂ���čĐ���ύX
	if (success)
	{
		GuideViewer::Instance()->SetData("����΂̔j��ɐ���",
			GuideActor::AnimState::Clapping,
			SoundConfig::MeteorBreakSuccess);
	}
	else
	{
		GuideViewer::Instance()->SetData("����΂̔j��Ɏ��s",
			GuideActor::AnimState::Defeat,
			SoundConfig::MeteorBreakFailed);
	}
	PlayBGM::Instance()->ResumePrev();
}

//=============================================================================
// �e���b�v�Đ��I���A覐Η����J�n
//=============================================================================
void CityDestroyEvent::MeteorFallStart(void)
{
	EventState = State::MeteorDebut;
	camera->SetTargetObject(Meteor);
}

//=============================================================================
// �A�ŃQ�[���̃J�E���g�_�E���J�n
//=============================================================================
void CityDestroyEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
	EventState = State::BeatGameStart;

	//�K�C�h�A�N�^�[�̃A�j���[�V����
	guideActor->ChangeAnim(GuideActor::AnimState::FightingIdle, true);

	TaskManager::Instance()->CreateDelayedTask(90, [&]()
	{
		guideActor->StartPunsh();
	});
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
		success = true;

		SE::Play(SoundConfig::SEID::Bom, 1.0f);
	}
	else
	{
		// ���s�A覐Η���
		EventState = State::BeatGameFail;
		success = false;
		
		D3DXVECTOR3 cameraPos = camera->GetPosition() + Vector3::Up * 30.0f;
		camera->Move(cameraPos, 10, 100.0f, []() {
			SE::Play(SoundConfig::SEID::Bom, 1.0f);
		});

		guideActor->SetActive(false);
	}
}

//=============================================================================
// �A�ŃQ�[���̌��ʂɂ��A�j���[�V�����J��
//=============================================================================
void CityDestroyEvent::OnFinisheBeat(bool result)
{
	guideActor->EndPunch(result);
}
