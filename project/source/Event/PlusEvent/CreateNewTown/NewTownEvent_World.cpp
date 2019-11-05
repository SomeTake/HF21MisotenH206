//=============================================================================
//
// �V������(�����x��)�C�x���g�N���X [NewTownEvent_World.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_World.h"
#include "../../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../../../Framework/Camera/CameraShakePlugin.h"
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
NewTownEvent_World::NewTownEvent_World(EventViewer *Ptr, std::function<void(void)> EventOverFunc) :
	EventBase(true),
	eventViewer(Ptr),
	EventOverFunc(EventOverFunc)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
NewTownEvent_World::~NewTownEvent_World()
{
	eventViewer = nullptr;
	NewTown = nullptr;
}

//=============================================================================
// ������
//=============================================================================
void NewTownEvent_World::Init()
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
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]() {CreateNewTown(); });
	});

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void NewTownEvent_World::Update()
{

}

//=============================================================================
// �`��
//=============================================================================
void NewTownEvent_World::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string NewTownEvent_World::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}

//=============================================================================
// �V�����������
//=============================================================================
void NewTownEvent_World::CreateNewTown(void)
{
	D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();
	D3DXVECTOR3 Amplitude = D3DXVECTOR3(10.0f, 5.0f, 10.0f);

	Camera::ShakePlugin::Instance()->Set(Amplitude,60);
	fieldEventHandler->CreateNewTown(NewTown);
	GameParticleManager::Instance()->SetSingularityEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(90, [&]() {EventOverFunc(); });
}

////=============================================================================
//// �C�x���g�I������
////=============================================================================
//void NewTownEvent_World::EventOver(void)
//{
//	// �C�x���g�I���A�Q�[�����s
//	Camera::TranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}