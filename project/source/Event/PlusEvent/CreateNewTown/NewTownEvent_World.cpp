//=============================================================================
//
// �V������(�����x��)�C�x���g�N���X [NewTownEvent_World.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_World.h"
#include "../../../../Framework/Camera/CameraShakePlugin.h"
#include "../../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../../Effect/WorldParticleManager.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../../Field/Camera/EventCamera.h"
#include "../../../Sound/PlayBGM.h"
#include "../../../Sound/SoundConfig.h"
#include "../../../../Framework/Sound/SoundEffect.h"
#include "../../../Sound/PlayBGM.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
NewTownEvent_World::NewTownEvent_World(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera* camera) :
	EventBase(true),
	eventViewer(Ptr),
	EventOverFunc(EventOverFunc),
	camera(camera)
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
	NewTown = fieldEventHandler->GetAtlantisPlace();
	TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::Atlantis, [&]()
	{
		// �\��n�ɃJ�������ړ�������
		camera->Translation(TownPos, 30, [&]() {CreateNewTown(); });

		//BGM�t�F�[�h�A�E�g
		PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::World, 0.0f, 90, false);
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
	D3DXVECTOR3 Amplitude = D3DXVECTOR3(5.0f, 3.0f, 5.0f);

	CameraShakePlugin::Instance()->Set(Amplitude, 300);
	fieldEventHandler->CreateAtlantis(NewTown);
	WorldParticleManager::Instance()->SetAtlantisEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(180, [&]() 
	{
		camera->Return(15, EventOverFunc);
	});

	//SE::Play(SoundConfig::SEID::CreationEvent, 1.0f);
	SE::Play(SoundConfig::SEID::NewContinentSE, 1.0f);
	TaskManager::Instance()->CreateDelayedTask(60, [&]()
	{
		SE::Play(SoundConfig::SEID::CreationEvent, 1.0f);
	});
}

////=============================================================================
//// �C�x���g�I������
////=============================================================================
//void NewTownEvent_World::EventOver(void)
//{
//	// �C�x���g�I���A�Q�[�����s
//	CameraTranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}