//*****************************************************************************
// 11/15(��)�`�����͂܉���
//*****************************************************************************

//=============================================================================
//
// �A�ŃQ�[���C�x���g�N���X [BeatGame.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "BeatGame.h"
#include <mutex>
#include <iostream>
#include "../../Viewer/GameScene/Controller/BeatGameViewer.h"
#include "../../../Framework/Input/input.h"
#include "../../Reward/RewardController.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************

//�A�ł̉�
static const int goalInput = 20;

//��������
static const float readyTime = 3.0f;

//�Q�[������
static const float gameTime = 5.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
BeatGame::BeatGame(BeatGame::GameType type,
	BeatGameViewer *viewer,
	std::function<void(bool)> OnFinishTelop,
	std::function<void(bool)> onFinishEvent) :
	EventBase(false),
	TelopOver(false),
	isSuccess(false),
	isReady(false),
	isFinished(false),
	canSetReady(true),
	canSetGo(true),
	countInput(0),
	countFrame(0),
	OnFinishTelop(OnFinishTelop),
	beatGameViewer(viewer),
	onFinishBeat(onFinishEvent)
{
	//�Đ����̃C�x���g���Z�b�g
	playingEvent = type;

	//�Q�[���^�C�g�����Z�b�g
	beatGameViewer->SetGameTitle(GetGameTitle());

	//�p�����[�^�������l�ɃZ�b�g
	beatGameViewer->SetGameGauge(1.0f);
	beatGameViewer->SetRemainTime(gameTime);

	//�r���[���͍ŏ��͔�\��
	beatGameViewer->SetActive(false);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
BeatGame::~BeatGame()
{

}

//=============================================================================
// �X�V
//=============================================================================
void BeatGame::Update()
{
	// �e���b�v�Đ����܂��Q�[���I��
	if (!TelopOver || !UseFlag) return;

	if (!isReady)
	{
		//���f�B�[�e�L�X�g���Z�b�g
		SetReadyText();

		//�t���[���J�E���g�X�V
		countFrame++;

		//�������ԂɒB������
		if (countFrame / 30.0f >= readyTime)
		{
			//�t���[���J�E���g���Z�b�g
			countFrame = 0;

			//����������ԂɈڍs
			isReady = true;
		}
	}
	else
	{
		//�S�[�e�L�X�g���Z�b�g
		SetGoText();

		//�t���[���J�E���g�X�V
		countFrame++;

		//���̓J�E���g���X�V(*���ӁF�{�Ԃ͂ǂ̃L�[���͂ł�OK�ɂ���H)
		if (Keyboard::GetTrigger(DIK_C) || GamePad::GetTrigger(0, BUTTON_A))
		{
			countInput++;
		}

		//�r���A�[�̃p�����[�^���Z�b�g
		SetViewerParam();

		//��������������
		if (IsSuccess())
		{
			//���ʂ�ʒm
			if (onFinishBeat != nullptr)
			{
				onFinishBeat(true);
			}

			//�������U���g��\��
			beatGameViewer->SetResult(BeatResultViewer::Success, [&]() {EventOver(); });

			// �����[�h�ɔ��f
			RewardController::Instance()->SetRewardData(RC::Type::ButtonMashing, 1);

			//����
			isSuccess = true;

			//�I��
			isFinished = true;
		}

		//���s����������
		if (IsFailed())
		{
			//���ʂ�ʒm
			if (onFinishBeat != nullptr)
			{
				onFinishBeat(false);
			}

			//���s���U���g��\��
			beatGameViewer->SetResult(BeatResultViewer::Failed, [&]() {EventOver(); });

			//���s
			isSuccess = false;

			//�I��
			isFinished = true;
		}
	}
	beatGameViewer->Update();
}

//=============================================================================
// �`��
//=============================================================================
void BeatGame::Draw()
{
	if (!UseFlag)
		return;

	if (!TelopOver) return;

	beatGameViewer->Draw();
}

//=============================================================================
// ���f�B�[�e�L�X�g�Z�b�g����(��x�������s)
//=============================================================================
void BeatGame::SetReadyText(void)
{
	if (!canSetReady) return;

	beatGameViewer->SetReady();
	canSetReady = false;
}

//=============================================================================
// �S�[�e�L�X�g�Z�b�g����(��x�������s)
//=============================================================================
void BeatGame::SetGoText(void)
{
	if (!canSetGo) return;

	beatGameViewer->SetGo();
	canSetGo = false;
}

//=============================================================================
// �r���A�[�p�����[�^�̃Z�b�g����
//=============================================================================
void BeatGame::SetViewerParam(void)
{
	if (isFinished) return;

	float remainTime = gameTime - countFrame / 30.0f;
	float gaugeRatio = 1.0f - (float)((float)countInput / (float)goalInput);

	beatGameViewer->SetRemainTime(remainTime);
	beatGameViewer->SetGameGauge(gaugeRatio);
}

//=============================================================================
// �A�ŃQ�[���^�C�g���擾����
//=============================================================================
BeatTitleViewer::TitleID BeatGame::GetGameTitle(void)
{
	BeatTitleViewer::TitleID id;

	//id�U�蕪��
	switch (playingEvent)
	{
	case BeatGame::AILevelDecrease:
		id = BeatTitleViewer::CalmAI;
		break;

	case BeatGame::BanStockUse:
		id = BeatTitleViewer::CalmAI;
		break;

	case BeatGame::CityDestroyEvent:
		id = BeatTitleViewer::ProtectCity;
		break;

	default:
		break;
	}

	return id;
}

//=============================================================================
// �������������菈��
//=============================================================================
bool BeatGame::IsSuccess(void)
{
	if (isFinished) return false;

	return 	countInput >= goalInput;
}

//=============================================================================
// ���s���������菈��
//=============================================================================
bool BeatGame::IsFailed(void)
{
	if (isFinished) return false;

	return countFrame >= gameTime * 30;
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string BeatGame::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}

//=============================================================================
// �J�E���g�_�E���J�n
//=============================================================================
void BeatGame::CountdownStart(void)
{
	TelopOver = true;
	beatGameViewer->SetActive(true);
}

//=============================================================================
// �C�x���g�I��
//=============================================================================
void BeatGame::EventOver(void)
{
	OnFinishTelop(isSuccess);
	UseFlag = false;
	beatGameViewer->SetActive(false);
}