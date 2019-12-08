//=============================================================================
//
// �V�������C�x���g�R���g���[���[�N���X [NewTownEventCtrl.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEventCtrl.h"
#include "NewTownEvent_City.h"
#include "NewTownEvent_World.h"
#include "NewTownEvent_Space.h"

#include "../../../Field/Camera/Plugin/FieldCameraTranslationPlugin.h"
#include "../../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../../Field/Camera/EventCamera.h"

#include <typeinfo.h>
#include "../../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../../Framework/Sound/SoundEffect.h"
#include "../../../Sound/SoundConfig.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
NewTownEventCtrl::NewTownEventCtrl(EventViewer *Ptr, int FieldLevel, EventCamera *camera) :
	EventBase(true),
	eventViewer(Ptr),
	eventCamera(camera)
{
	eventCamera->Init();

	if (FieldLevel == Field::City)
	{
		NewTownEvent = new NewTownEvent_City(Ptr, [&]() {EventOver(); }, camera);
	}
	else if (FieldLevel == Field::World)
	{
		NewTownEvent = new NewTownEvent_World(Ptr, [&]() {EventOver(); }, camera);
	}
	else if (FieldLevel == Field::Space)
	{
		NewTownEvent = new NewTownEvent_Space(Ptr, [&]() {EventOver(); }, camera);
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
NewTownEventCtrl::~NewTownEventCtrl()
{
	eventViewer = nullptr;
	eventCamera = nullptr;
	SAFE_DELETE(NewTownEvent);
}

//=============================================================================
// ������
//=============================================================================
void NewTownEventCtrl::Init()
{
	NewTownEvent->Init();

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void NewTownEventCtrl::Update()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	NewTownEvent->Update();
}

//=============================================================================
// �`��
//=============================================================================
void NewTownEventCtrl::Draw()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	NewTownEvent->Draw();
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string NewTownEventCtrl::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}

//=============================================================================
// �C�x���g�I������
//=============================================================================
void NewTownEventCtrl::EventOver(void)
{
	// �C�x���g�I���A�Q�[�����s
	eventCamera->Restore();
	fieldEventHandler->ResumeGame();
	UseFlag = false;

	// ���ݔ������Ă���C�x���g�ɍ��킹�čĐ���ύX
	if (typeid(*NewTownEvent) == typeid(NewTownEvent_City))
	{
		GuideViewer::Instance()->SetMessage("�V���������o�����܂���");
		GuideViewer::Instance()->ChangeAnim(GuideActor::AnimState::Yeah);
		SE::Play(SoundConfig::NewTown, 1.0);
	}
	else if (typeid(*NewTownEvent) == typeid(NewTownEvent_World))
	{
		GuideViewer::Instance()->SetMessage("�V�����嗤���o�����܂���");
		GuideViewer::Instance()->ChangeAnim(GuideActor::AnimState::Yeah);
		SE::Play(SoundConfig::NewContinent, 1.0);
	}
	else if (typeid(*NewTownEvent) == typeid(NewTownEvent_Space))
	{
		GuideViewer::Instance()->SetMessage("�V���������a�����܂���");
		GuideViewer::Instance()->ChangeAnim(GuideActor::AnimState::Yeah);
		SE::Play(SoundConfig::NewStar, 1.0);
	}

}