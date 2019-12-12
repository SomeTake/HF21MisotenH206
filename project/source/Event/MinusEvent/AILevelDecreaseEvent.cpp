//=============================================================================
//
// AI���x�������C�x���g�N���X [AILevelDecreaseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "AILevelDecreaseEvent.h"
#include "BeatGame.h"
#include "../EventActor/UFOActor.h"
#include "../../Field/Place/FieldPlaceModel.h"
#include "../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Field/Camera/EventCamera.h"
#include "../../Viewer/GameScene/Controller/BeatGameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideActor.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"
#include "../../Sound/PlayBGM.h"
#include "../../Booth/BoothController.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// UFO�̍~�����x
const float FallSpeed = 0.2f;
// AI���x�����炷�̌��ʒl
const float DecreasePercent = -0.1f;
// UFO���f���̃X�P�[��
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);
// �f�t�H���g�̍���
const float DefaultHeight = 50.0f;

enum State
{
	TelopExpanding,
	UFODebut,
	BeatGameStart,
	BeatGameSuccess,
	BeatGameFail,
	EffectHappend,
	UFOExit,
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
AILevelDecreaseEvent::AILevelDecreaseEvent(EventViewer* eventViewer, EventCamera *camera, BeatGameViewer *beatViewer) :
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
AILevelDecreaseEvent::~AILevelDecreaseEvent()
{
	SAFE_DELETE(beatGame);
	SAFE_DELETE(UFO);
	SAFE_DELETE(guideActor);
	eventViewer = nullptr;
}


//=============================================================================
// ������
//=============================================================================
void AILevelDecreaseEvent::Init()
{
	//�J�������C�x���g�J�����ɐ؂�ւ�
	camera->Init();

	// �A�ŃQ�[���C���X�^���X
	auto onFinishBeat = std::bind(&AILevelDecreaseEvent::OnFinishBeat, this, std::placeholders::_1);
	beatGame = new BeatGame(BeatGame::AILevelDecrease, beatViewer, [&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); }, onFinishBeat);

	// �ڕW���̗\��n���擾
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// �������W�ݒ�
	UFOPos = TownPos + Vector3::Up * DefaultHeight;

	// UFO���b�V���쐬
	UFO = new UFOActor(UFOPos, Scale, "UFO");

	//�K�C�h�쐬
	guideActor = new GuideActor();
	guideActor->SetActive(false);
	guideActor->SetScale(Vector3::One * 0.05f);

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::Alien, [&]()
	{
		camera->Translation(TownPos, 30, [&]() {
			PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::UFOEvent, 0.1f, 30);
			UFODebutStart(); 
		});
	});

	//�u�[�X��LED��_�ł�����
	BoothController::Instance()->BlinkLED(false);
		
	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void AILevelDecreaseEvent::Update()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	float Distance = 0.0f;

	switch (EventState)
	{
		// UFO�o��
	case UFODebut:
		//UFO�̈ړ��A�C�x���g�J�ڂ�Tween�ɔC����
		UFOPos = UFO->GetPosition();
		break;

	case BeatGameStart:

		UFO->Update();

		// �A�ŃQ�[���̍X�V
		beatGame->Update();

		//�K�C�h��UFO�Ɍ�������
		guideActor->LookAt(UFOPos);

		break;

		// UFO����
	case BeatGameSuccess:

		// UFO���ăG�t�F�N�g
		GameParticleManager::Instance()->SetMeteorExplosionEffect(UFOPos);
		// 30�t���[���̒x����ݒu
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			camera->Return(30, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
		PlayBGM::Instance()->FadeOut();
		break;

		// AI���x�����炷
	case BeatGameFail:

		UFO->Update();
		PlayBGM::Instance()->FadeOut();

		break;

		// UFO�ޏ�
	case UFOExit:

		UFOPos = UFO->GetPosition();
		//UFO�̈ړ��A�C�x���g�J�ڂ�Tween�ɔC����
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
void AILevelDecreaseEvent::Draw()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	if (EventState != State::EffectHappend)
	{
		UFO->Draw();
	}

	if (guideActor->IsActive())
		guideActor->Draw();

	beatGame->Draw();
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string AILevelDecreaseEvent::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}

//=============================================================================
// UFO���o��J�n
//=============================================================================
void AILevelDecreaseEvent::UFODebutStart(void)
{
	//�J�����̈ʒu��؂�ւ�
	D3DXVECTOR3 cameraPos = TownPos + D3DXVECTOR3(15.0f, 15.0f, -15.0f);
	camera->Move(cameraPos, 10, 10.0f);
	camera->SetTargetObject(UFO);

	//UFO�o��
	Tween::Move(*UFO, TownPos + Vector3::Up * 25.0f, 60, EaseType::InOutCirc, [&]()
	{
		CountdownStart();
	});

	EventState = UFODebut;
}

//=============================================================================
// �C�x���g�I������
//=============================================================================
void AILevelDecreaseEvent::EventOver(void)
{
	// �C�x���g�I���A�Q�[�����s
	camera->Restore();
	fieldEventHandler->ResumeGame();
	UseFlag = false;

	if (success)
	{
		GuideViewer::Instance()->SetData("�F���l�̐N�U��H���~�߂܂���",
			GuideActor::AnimState::Salute,
			SoundConfig::UFOSuccess);
	}
	else
	{
		GuideViewer::Instance()->SetData("�����N���x����������܂�",
			GuideActor::AnimState::Pain,
			SoundConfig::UFOFailed);
	}
	PlayBGM::Instance()->ResumePrev();
}

//=============================================================================
// �A�ŃQ�[���̌��ʂɂ��K�C�h�̃A�j���[�V�����J��
//=============================================================================
void AILevelDecreaseEvent::OnFinishBeat(bool result)
{
	guideActor->EndPunch(result);
}

//=============================================================================
// �G�t�F�N�g�I�����̏���
//=============================================================================
void AILevelDecreaseEvent::OnFinishEffect()
{
	Tween::Move(*UFO, TownPos + Vector3::Up * DefaultHeight, 90, EaseType::InCirc, [&]()
	{
		camera->Return(30, [&]() { EventOver(); });
		EventState = EffectHappend;
	});

	EventState = UFOExit;
}

//=============================================================================
// �A�ŃQ�[���̃J�E���g�_�E���J�n
//=============================================================================
void AILevelDecreaseEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
	UFO->SetHoverMotion(true);

	//�J�����̒Ǐ]��؂�
	camera->SetTargetObject(nullptr);
	
	//�K�C�h�L�����o��
	D3DXVECTOR3 diff = Vector3::Normalize(camera->GetPosition() - UFOPos);
	D3DXVECTOR3 guidePos = UFOPos + diff * 7.0f + Vector3::Down * 2.0f;

	guideActor->SetPosition(TownPos);
	guideActor->Move(guidePos, 60);

	guideActor->ChangeAnim(GuideActor::AnimState::FightingIdle, true);

	guideActor->SetActive(true);

	TaskManager::Instance()->CreateDelayedTask(90, [&]()
	{
		guideActor->StartPunsh();
	});

	EventState = State::BeatGameStart;
}

//=============================================================================
// �A�ŃQ�[���̌��ʂɂ�鏈��
//=============================================================================
void AILevelDecreaseEvent::ReceiveBeatResult(bool IsSuccess)
{
	if (IsSuccess)
	{
		// ����
		EventState = BeatGameSuccess;
		success = true;
	}
	else
	{
		// ���s
		TaskManager::Instance()->CreateDelayedTask(90, [&]()
		{
			OnFinishEffect();
		});

		// �G�t�F�N�g
		GameParticleManager::Instance()->SetDarknessEffect(TownPos);

		fieldEventHandler->AdjustLevelAI(DecreasePercent);
		EventState = BeatGameFail;
		success = false;

		//�K�C�h�L�����Ɏ��s���[�V������������
		guideActor->ChangeAnim(GuideActor::AnimState::Defeat, true);
	}
}


