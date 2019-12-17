//=============================================================================
//
// �V������(�s�s���x��)�C�x���g�N���X [NewTownEvent_City.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_City.h"
#include "../../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../../Effect/CityParticleManager.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../../Field/Camera/EventCamera.h"
#include "../../../../Framework/Sound/SoundEffect.h"
#include "../../../Sound/SoundConfig.h"
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
NewTownEvent_City::NewTownEvent_City(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera *camera) :
	EventBase(true),
	eventViewer(Ptr),
	EventOverFunc(EventOverFunc),
	camera(camera)
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
	TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::Singularity, [&]()
	{
		// �\��n�ɃJ�������ړ�������
		camera->Translation(TownPos, 30, [&]() {CreateNewTown(); });

		//BGM�t�F�[�h�A�E�g
		PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::City, 0.0f, 90, false);
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
	CityParticleManager::Instance()->SetSingularityEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(90, [&]() 
	{
		camera->Return(15, EventOverFunc);
	});

	//SE::Play(SoundConfig::SEID::CreationEvent, 1.0f);
	SE::Play(SoundConfig::SEID::NewTownSE, 0.3f);
	TaskManager::Instance()->CreateDelayedTask(60, [&]()
	{
		SE::Play(SoundConfig::SEID::CreationEvent, 1.0f);
	});
}
