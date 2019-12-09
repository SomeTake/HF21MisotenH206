//=============================================================================
//
// �L���l�C�x���g�N���X [FamousPeopleEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "FamousPeopleEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �{�[�i�X���l
const float BonusNum = 1.5f;
// �f�t�H���g�̃{�[�i�X���ʃt���[��
const int DefalutBonusFrame = 150;
const std::string FamousPeopleEvent::message[] = {
	{"�ŋ߃u�[���̌|�l�������̒��ɂ������I"},
	{"M-1�D���|�l�����̒��̊ό���g�ɁI�H"},
	{"���ɂ���}����D���D���N"}
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
FamousPeopleEvent::FamousPeopleEvent() :
	EventBase(false),
	RemainTime(DefalutBonusFrame)
{
	fieldEventHandler->SetDevelopBonus(BonusNum);
	GuideViewer::Instance()->SetData("��莞�Ԕ��W�x���㏸���܂�",
		GuideActor::AnimState::FistPump,
		SoundConfig::DevelopSpeedUp);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
FamousPeopleEvent::~FamousPeopleEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void FamousPeopleEvent::Update()
{
	RemainTime--;
	if (RemainTime <= 0)
	{
		// �{�[�i�X��~����
		fieldEventHandler->SetDevelopBonus(1.0f);

		UseFlag = false;
	}
}

//=============================================================================
// �`��
//=============================================================================
void FamousPeopleEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string FamousPeopleEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	int r = rand() % 3;
	MessageContainer.push_back(message[r]);

	if (!MessageContainer.empty())
	{
		int MessageNo = rand() % MessageContainer.size();
		return MessageContainer.at(MessageNo);
	}
	else
	{
		string ErrMsg = "�C�x���g���b�Z�[�W������܂���";
		return ErrMsg;
	}
}
