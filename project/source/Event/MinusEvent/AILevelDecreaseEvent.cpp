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
	beatViewer(beatViewer)
{

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
	beatGame = new BeatGame(BeatGame::AILevelDecrease, beatViewer, [&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

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
		camera->Translation(TownPos, 30, [&]() {UFODebutStart(); });
	});

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

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(UFOPos - TownPos));

		if (Distance > pow(25.0f, 2))
		{
			UFOPos += Vector3::Down * FallSpeed;
			UFO->SetPosition(UFOPos);
		}
		else
		{
			CountdownStart();
			EventState = State::BeatGameStart;
		}
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
		break;

		// AI���x�����炷
	case BeatGameFail:

		UFO->Update();

		// �G�t�F�N�g
		GameParticleManager::Instance()->SetDarknessEffect(TownPos);
		TaskManager::Instance()->CreateDelayedTask(90, [&]()
		{
			EventState = UFOExit;
		});
		break;

		// UFO�ޏ�
	case UFOExit:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(UFOPos - TownPos));

		if (Distance < pow(DefaultHeight, 2))
		{
			UFOPos += Vector3::Up * FallSpeed;
			UFO->SetPosition(UFOPos);
		}
		else
		{
			camera->Return(30, [&]() { EventOver(); });
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
	D3DXVECTOR3 guidePos = UFOPos + diff * 5.0f + Vector3::Down * 2.0f;

	Tween::Move(*guideActor, TownPos, guidePos, 15, EaseType::OutCubic);

	guideActor->SetActive(true);
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
	}
	else
	{
		// ���s
		fieldEventHandler->AdjustLevelAI(DecreasePercent);
		EventState = BeatGameFail;

		//�K�C�h�L�����Ɏ��s���[�V������������
		guideActor->ChangeAnim(GuideActor::AnimState::Defeat);
	}
}


