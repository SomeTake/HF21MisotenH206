//=============================================================================
//
// �L���l�C�x���g�N���X [FamousPeopleEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "FamousPeopleEvent.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �{�[�i�X���l
const float BonusNum = 1.5f;
// �f�t�H���g�̃{�[�i�X���ʃt���[��
const int DefalutBonusFrame = 150;

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

	if (FieldLevel == Field::City)
	{
		MessageContainer.push_back("�|�l���X�ɗ����I\n���W���x�A�b�v�I");
	}
	else if (FieldLevel == Field::World)
	{
		MessageContainer.push_back("�|�l���X�ɗ����I\n���W���x�A�b�v�I");
	}
	else if (FieldLevel == Field::Space)
	{
		MessageContainer.push_back("�|�l���X�ɗ����I\n���W���x�A�b�v�I");
	}

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
