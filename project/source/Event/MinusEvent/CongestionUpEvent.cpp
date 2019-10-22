//=============================================================================
//
// ���G�x�㏸�C�x���g�N���X [CongestionUpEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "CongestionUpEvent.h"
#include "../EventConfig.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const float CongestionBias = 1.0f;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CongestionUpEvent::CongestionUpEvent(int RemainTime) : RemainTime(RemainTime)
{
	fieldController->RaiseTrafficJam(CongestionBias);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CongestionUpEvent::~CongestionUpEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void CongestionUpEvent::Update()
{
	RemainTime--;
	if (RemainTime <= 0)
	{
		fieldController->RaiseTrafficJam(0.0f);
		UseFlag = false;
	}
}

//=============================================================================
// �`��
//=============================================================================
void CongestionUpEvent::Draw()
{
	
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string CongestionUpEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("�����_���G�x�㏸�C�x���g");
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
