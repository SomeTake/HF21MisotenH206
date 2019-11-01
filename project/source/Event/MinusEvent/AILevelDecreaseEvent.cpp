//=============================================================================
//
// AI���x�������C�x���g�N���X [AILevelDecreaseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "AILevelDecreaseEvent.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const float DecreasePercent = -0.1f;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
AILevelDecreaseEvent::AILevelDecreaseEvent() :
	EventBase(true)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
AILevelDecreaseEvent::~AILevelDecreaseEvent()
{

}


//=============================================================================
// ������
//=============================================================================
void AILevelDecreaseEvent::Init()
{
	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void AILevelDecreaseEvent::Update()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	fieldEventHandler->AdjustLevelAI(DecreasePercent);

	// �C�x���g�I���A�Q�[�����s
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void AILevelDecreaseEvent::Draw()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string AILevelDecreaseEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("AI���x�����炷�C�x���g");
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
