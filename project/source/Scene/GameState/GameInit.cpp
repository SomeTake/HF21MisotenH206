//=====================================
//
//GameInit.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameInit.h"
#include "../../../Framework/Renderer3D/SkyBox.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Field/FieldController.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../Effect/GameParticleManager.h"
#include "../../Field/Camera/Plugin/FieldCameraTranslationPlugin.h"
#include "../../../Framework/Camera/CameraShakePlugin.h"
#include "../../../Framework/PostEffect/BloomController.h"
#include "../../../Framework/Core/PlayerPrefs.h"
#include "../../GameConfig.h"
#include "../../../Framework/Sound/BackgroundMusic.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../Viewer/GameScene/Controller/NameEntryViewer.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{	
	// �C�x���g�p���f��
	ResourceManager::Instance()->LoadMesh("Meteor", "data/MODEL/Planet/Meteor.x");
	ResourceManager::Instance()->LoadMesh("UFO", "data/MODEL/UFO/UFO.x");

	// �g�p���Ȃ�UI�̕`���OFF�i�^�C�g���A���U���g�p�Ȃǁj
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	GuideViewer::Instance()->SetActive(false);
	//entity.guideViewer->SetActive(false);
	entity.resultViewer->SetActive(false);
	entity.nemeEntryViewer->SetActive(false);

	//�p�[�e�B�N��������
	entity.levelParticleManager->Init();

	//�J�����Ƀv���O�C����ǉ����ď�����
	entity.fieldCamera->AddPlugin(FieldCameraTranslationPlugin::Instance());
	entity.fieldCamera->AddPlugin(CameraShakePlugin::Instance());
	FieldCameraTranslationPlugin::Instance()->Init();

	//�J�����̒Ǐ]�ڕW�ɃJ�[�\����ݒ肵�ă��[�h�ؑ�
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

	//CSV�f�[�^�����[�h
	entity.field->Load();

	//�C�x���g�n���h���ݒ�
	entity.SetEventHandler();

	//�u���[���G�t�F�N�g�̃p�����[�^�ݒ�
	entity.bloomController->SetPower(entity.BloomPower[0], entity.BloomPower[1], entity.BloomPower[2]);
	entity.bloomController->SetThrethold(entity.BloomThrethold[0], entity.BloomThrethold[1], entity.BloomThrethold[2]);

	//�T�E���h�ǂݍ���
	//NOTE : ���͂������B�{�Ԃł͂����ƃ^�O��p�ӂ���
	BGM::Load("data/SOUND/BGM/Course_Select.wav", 0);
	BGM::FadeIn(0, 0.1f, 30);
	for (int i = 0; i < SE::VoiceType::Max; i++)
	{
		SE::Load(SE::path[i], SE::VoiceType(i));
	}

	//�������ԓǂݍ���
	entity.remainTime = PlayerPrefs::GetNumber<int>(Utility::ToString(GameConfig::Key_RemainTime));

	//�^�C�g���ɑJ��
	entity.ChangeState(State::Title);
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameInit::OnUpdate(GameScene & entity)
{
	entity.field->UpdateObject();
	return GameScene::State::Initialize;
}
