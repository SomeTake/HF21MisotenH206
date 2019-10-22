//=============================================================================
//
// �����N���x�������C�x���g�N���X [LinkLevelDecreaseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "LinkLevelDecreaseEvent.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const int LinkLevelDecreaseNum = -1;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
LinkLevelDecreaseEvent::LinkLevelDecreaseEvent()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
LinkLevelDecreaseEvent::~LinkLevelDecreaseEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void LinkLevelDecreaseEvent::Update()
{
	fieldController->AdjustAllLinkLevel(LinkLevelDecreaseNum);
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void LinkLevelDecreaseEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string LinkLevelDecreaseEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("�����N���x�����炷�C�x���g");
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