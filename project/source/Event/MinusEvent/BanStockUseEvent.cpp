//=============================================================================
//
// �X�g�b�N�g�p�s�C�x���g�N���X [BanStockUseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "BanStockUseEvent.h"
#include "../MinusEvent/BeatGame.h"
#include "../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �f�t�H���g�̌��ʎ���
const int DefaultDebuffFrame = 300;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
BanStockUseEvent::BanStockUseEvent(EventViewer* eventViewer,
	BeatGameViewer *beatViewer,
	std::function<void(bool)> SetBanStock,
	std::function<bool(void)> GetInPause) :
	EventBase(true),
	RemainTime(DefaultDebuffFrame),
	InDebuff(false),
	SetBanStock(SetBanStock),
	GetInPause(GetInPause),
	eventViewer(eventViewer),
	beatViewer(beatViewer)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
BanStockUseEvent::~BanStockUseEvent()
{
	SAFE_DELETE(beatGame);
	eventViewer = nullptr;
}

//=============================================================================
// ������
//=============================================================================
void BanStockUseEvent::Init()
{
	// �A�ŃQ�[���C���X�^���X
	beatGame = new BeatGame(BeatGame::BanStockUse, beatViewer, [&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::AI_Strike, nullptr);

	// �{���G�t�F�N�g�ݒu
	GameParticleManager::Instance()->SetAngryFaceEffect();

	// �{���G�t�F�N�g�I���܂ő҂�
	TaskManager::Instance()->CreateDelayedTask(150, [&]() {	beatGame->CountdownStart(); });

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void BanStockUseEvent::Update()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	beatGame->Update();

	if (InDebuff && !GetInPause())
	{
		RemainTime--;
		if (RemainTime <= 0)
		{
			// �������
			fieldEventHandler->SealUsingItem(false);
			SetBanStock(false);
			UseFlag = false;
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void BanStockUseEvent::Draw()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	beatGame->Draw();
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string BanStockUseEvent::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}

//=============================================================================
// �C�x���g�I������
//=============================================================================
void BanStockUseEvent::EventOver(void)
{
	// �C�x���g�I���A�Q�[�����s
	SetBanStock(false);
	fieldEventHandler->ResumeGame();
	UseFlag = false;

	GuideViewer::Instance()->SetData("AI�̖\����H���~�߂܂���",
		GuideActor::AnimState::Salute, 
		SE::VoiceType::AIOutofControllStop);

}

//=============================================================================
// �A�ŃQ�[���̌��ʂɂ�鏈��
//=============================================================================
void BanStockUseEvent::ReceiveBeatResult(bool IsSuccess)
{
	if (IsSuccess)
	{
		// ����
		EventOver();
	}
	else
	{
		// ���s�A�X�g�b�N�g�p����
		fieldEventHandler->SealUsingItem(true);
		InDebuff = true;
		SetBanStock(true);
		fieldEventHandler->ResumeGame();

		GuideViewer::Instance()->SetData("��莞�ԃh�������g���Ȃ��Ȃ�܂�",
			GuideActor::AnimState::Pain,
			SE::VoiceType::AIOutofControll);

	}
}

