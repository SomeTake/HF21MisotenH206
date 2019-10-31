//=============================================================================
//
// �V�������C�x���g�N���X [NewCityEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "NewCityEvent.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
NewCityEvent::NewCityEvent(EventViewer *Ptr) : 
	EventBase(true),
	eventViewer(Ptr)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
NewCityEvent::~NewCityEvent()
{
	eventViewer = nullptr;
}

//=============================================================================
// ������
//=============================================================================
void NewCityEvent::Init()
{
	// �V�����������\��n���擾
	NewTown = fieldEventHandler->GetNewTownPosition();
	const D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(PositiveEvent01, [=]()
	{
		// �\��n�ɃJ�������ړ�������
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]() {CreateNewCity(); });
	});

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void NewCityEvent::Update()
{

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
	// �k��
	return "";
}

//=============================================================================
// �V�����������
//=============================================================================
void NewCityEvent::CreateNewCity(void)
{
	const D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	fieldEventHandler->CreateNewTown(NewTown);
	GameParticleManager::Instance()->SetSingularityEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(90, [&]() {EventOver(); });
}

//=============================================================================
// �C�x���g�I������
//=============================================================================
void NewCityEvent::EventOver(void)
{
	// �C�x���g�I���A�Q�[�����s
	Camera::TranslationPlugin::Instance()->Restore(30, nullptr);
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}