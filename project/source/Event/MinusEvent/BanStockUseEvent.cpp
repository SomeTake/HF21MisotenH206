//=============================================================================
//
// �X�g�b�N�g�p�s�C�x���g�N���X [BanStockUseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "BanStockUseEvent.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
BanStockUseEvent::BanStockUseEvent(int RemainTime) : RemainTime(RemainTime)
{
	// �X�g�b�N�g�p����
	fieldController->SealUsingItem(true);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
BanStockUseEvent::~BanStockUseEvent()
{

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
		fieldController->SealUsingItem(false);
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
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("�X�g�b�N�g�p�֎~�C�x���g");
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
