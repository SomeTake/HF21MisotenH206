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
const float BonusNum = 1.5f;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
FamousPeopleEvent::FamousPeopleEvent(int RemainTime) : RemainTime(RemainTime)
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

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("�����ւ�悭�ł��܂����I");
	}
	else if (FieldLevel == Field::Model::World)
	{

	}
	else if (FieldLevel == Field::Model::Space)
	{

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
