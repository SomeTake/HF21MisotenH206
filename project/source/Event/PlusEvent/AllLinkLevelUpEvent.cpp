//=============================================================================
//
// ���S�̃����N���x���㏸�C�x���g�N���X [AllLinkLevelUpEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "AllLinkLevelUpEvent.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const int LinkLevelUpNum = 1;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
AllLinkLevelUpEvent::AllLinkLevelUpEvent() :
	EventBase(false)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
AllLinkLevelUpEvent::~AllLinkLevelUpEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void AllLinkLevelUpEvent::Update()
{
	fieldEventHandler->AdjustAllLinkLevel(LinkLevelUpNum);
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void AllLinkLevelUpEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string AllLinkLevelUpEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::City)
	{
		MessageContainer.push_back("�I�����s�b�N�J�ÁI\n�S�Ă̊X�̃����N���x���㏸�I");
	}
	else if (FieldLevel == Field::World)
	{
		MessageContainer.push_back("�I�����s�b�N�J�ÁI\n�S�Ă̊X�̃����N���x���㏸�I");
	}
	else if (FieldLevel == Field::Space)
	{
		MessageContainer.push_back("�I�����s�b�N�J�ÁI\n�S�Ă̊X�̃����N���x���㏸�I");
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
