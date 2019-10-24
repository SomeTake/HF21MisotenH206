//=============================================================================
//
// �V�������C�x���g�N���X [NewCityEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "NewCityEvent.h"

#include "../../../Framework/Camera/CameraTranslationPlugin.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
NewCityEvent::NewCityEvent(EventViewer *Ptr) : eventViewer(Ptr)
{
	// �V�����������\��n���擾
	NewTown = fieldEventHandler->GetNewTownPosition();
	const D3DXVECTOR3 TownPosVec3 = NewTown->GetPosition().ConvertToWorldPosition();

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(PositiveEvent01, [=]()
	{
		// �\��n�ɃJ�������ړ�������
		Camera::TranslationPlugin::Instance()->Move(
			TownPosVec3,
			30,
			// �V�����������֐��̃����_��
			[&]()
		{
			fieldEventHandler->CreateNewTown(NewTown);
			Camera::TranslationPlugin::Instance()->Restore(30, nullptr);
		});
	});
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
NewCityEvent::~NewCityEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void NewCityEvent::Update()
{
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void NewCityEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string NewCityEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("�悤�����W���p���p�[�N��");
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
