//=============================================================================
//
// �X�g�b�N�g�p�s�C�x���g�N���X [BanStockUseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "BanStockUseEvent.h"
#include "../MinusEvent/BeatGame.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"


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
BanStockUseEvent::BanStockUseEvent(EventViewer* eventViewer) :
	RemainTime(DefaultDebuffFrame)
{
	// �A�ŃQ�[���C���X�^���X
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(NegativeEvent01, nullptr);

	// �{���G�t�F�N�g�ݒu
	GameParticleManager::Instance()->SetAngryFaceEffect();

	TaskManager::Instance()->CreateDelayedTask(90, [&]() {CountdownStart(); });
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
BanStockUseEvent::~BanStockUseEvent()
{
	SAFE_DELETE(beatGame);
}

//=============================================================================
// �X�V
//=============================================================================
void BanStockUseEvent::Update()
{
	RemainTime--;
	if (RemainTime <= 0)
	{
		// �������
		fieldEventHandler->SealUsingItem(false);
		UseFlag = false;
	}
}

//=============================================================================
// �`��
//=============================================================================
void BanStockUseEvent::Draw()
{

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
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}

//=============================================================================
// �A�ŃQ�[���̃J�E���g�_�E���J�n
//=============================================================================
void BanStockUseEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
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
	}
}

