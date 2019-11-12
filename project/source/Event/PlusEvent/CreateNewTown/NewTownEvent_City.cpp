//=============================================================================
//
// �V������(�s�s���x��)�C�x���g�N���X [NewTownEvent_City.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_City.h"
#include "../../../Field/Camera/Plugin/FieldCameraTranslationPlugin.h"
#include "../../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../../Framework/Task/TaskManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
NewTownEvent_City::NewTownEvent_City(EventViewer *Ptr, std::function<void(void)> EventOverFunc) :
	EventBase(true),
	eventViewer(Ptr),
	EventOverFunc(EventOverFunc)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
NewTownEvent_City::~NewTownEvent_City()
{
	eventViewer = nullptr;
	NewTown = nullptr;
}

//=============================================================================
// ������
//=============================================================================
void NewTownEvent_City::Init()
{
	// �V�����������\��n���擾
	NewTown = fieldEventHandler->GetNewTownPosition();
	const D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::NewPlanet, [=]()
	{
		// �\��n�ɃJ�������ړ�������
		FieldCameraTranslationPlugin::Instance()->Move(TownPos, 30, [&]() {CreateNewTown(); });
	});

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void NewTownEvent_City::Update()
{

}

//=============================================================================
// �`��
//=============================================================================
void NewTownEvent_City::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string NewTownEvent_City::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}

//=============================================================================
// �V�����������
//=============================================================================
void NewTownEvent_City::CreateNewTown(void)
{
	D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	fieldEventHandler->CreateNewTown(NewTown);
	GameParticleManager::Instance()->SetSingularityEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(90, [&]() {EventOverFunc(); });
}

////=============================================================================
//// �C�x���g�I������
////=============================================================================
//void NewTownEvent_City::EventOver(void)
//{
//	// �C�x���g�I���A�Q�[�����s
//	CameraTranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}