//=============================================================================
//
// AI���x�������C�x���g�N���X [AILevelDecreaseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "AILevelDecreaseEvent.h"
#include "BeatGame.h"
#include "../EventActor.h"
#include "../../Field/Place/FieldPlaceModel.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../../Framework/Task/TaskManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// UFO�̍~�����x
const float FallSpeed = 0.2f;
// AI���x�����炷�̌��ʒl
const float DecreasePercent = -0.1f;
// UFO���f���̃X�P�[��
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);

enum State
{
	TelopExpanding,
	UFODebut,
	BeatGameStart,
	BeatGameSuccess,
	BeatGameFail,
	EffectHappend,
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
AILevelDecreaseEvent::AILevelDecreaseEvent(EventViewer* eventViewer) :
	EventBase(true),
	EventState(State::TelopExpanding),
	eventViewer(eventViewer)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
AILevelDecreaseEvent::~AILevelDecreaseEvent()
{
	SAFE_DELETE(beatGame);
	SAFE_DELETE(UFO);
	eventViewer = nullptr;
}


//=============================================================================
// ������
//=============================================================================
void AILevelDecreaseEvent::Init()
{
	// �A�ŃQ�[���C���X�^���X
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// �ڕW���̗\��n���擾
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// 覐Η��������v�Z
	UFOPos = TownPos + Vector3::Up * 40.0f;

	// 覐΃��b�V���쐬
	UFO = new EventActor(UFOPos, Scale, "UFO");

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(NegativeEvent01, [&]()
	{
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]() {UFODebutStart(); });
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
	case UFODebut:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(UFOPos - TownPos));

		if (Distance > pow(25.0f, 2))
		{
			UFOPos += Vector3::Down * FallSpeed;
		}
		else
		{
			CountdownStart();
			EventState = State::BeatGameStart;
		}
		break;

	case BeatGameStart:

		/*float RadiusX = 1.0f;
		float RadiusY = 2.0f;
		float RadiusZ = 3.0f;
		float RateX = 3.0f;
		float RateY = 4.0f;
		float RateZ = 5.0f;

		D3DXVECTOR3 hover = D3DXVECTOR3
		{
				RadiusX * sinf(RateX * (float)FrameCount),
				RadiusY * sinf(RateY * (float)FrameCount),
				RadiusZ * sinf(RateZ * (float)FrameCount)
		};

		UFOPos += hover;*/

		// �A�ŃQ�[���̍X�V
		beatGame->Update();
		break;

		// UFO����
	case BeatGameSuccess:

		// UFO���ăG�t�F�N�g
		GameParticleManager::Instance()->SetMeteorExplosionEffect(UFOPos);
		// 30�t���[���̒x����ݒu
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			Camera::TranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
		break;

		// AI���x�����炷
	case BeatGameFail:

		// 30�t���[���̒x����ݒu
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			Camera::TranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
		break;

	default:
		break;
	}
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
		UFO->SetPosition(UFOPos);
		UFO->Draw();
	}

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
	EventState = UFODebut;
}


//=============================================================================
// �C�x���g�I������
//=============================================================================
void AILevelDecreaseEvent::EventOver(void)
{
	// �C�x���g�I���A�Q�[�����s
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}

//=============================================================================
// �A�ŃQ�[���̃J�E���g�_�E���J�n
//=============================================================================
void AILevelDecreaseEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
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
	}
}


