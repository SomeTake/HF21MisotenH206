//=============================================================================
//
// �����x�������C�x���g�N���X [CityLevelDecreaseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "CityLevelDecreaseEvent.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const int CityLevelDecreaseNum = -1;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CityLevelDecreaseEvent::CityLevelDecreaseEvent()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CityLevelDecreaseEvent::~CityLevelDecreaseEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void CityLevelDecreaseEvent::Update()
{
	fieldController->AdjustLevelDevelopment(CityLevelDecreaseNum);
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void CityLevelDecreaseEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string CityLevelDecreaseEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("�����x�����炷�C�x���g");
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
