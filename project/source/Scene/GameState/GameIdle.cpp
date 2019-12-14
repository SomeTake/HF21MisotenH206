//=====================================
//
//Template.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameIdle.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Tool/ProfilerCPU.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/TitleScene/TitleViewer.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	ProfilerCPU::Instance()->Begin("Update Event");
	entity.eventController->Update();
	entity.eventController->UpdateViewer();
	ProfilerCPU::Instance()->End("Update Event");

	//���͊m�F
	entity.field->CheckInput();

	//�t�B�[���h�X�V
	ProfilerCPU::Instance()->Begin("Update Logic");
	entity.field->UpdateLogic();
	ProfilerCPU::Instance()->End("Update Logic");

	ProfilerCPU::Instance()->Begin("Update FieldObject");
	entity.field->UpdateObject();
	ProfilerCPU::Instance()->End("Update FieldObject");

	//�������ԃJ�E���g
	entity.remainTime = Math::Max(0, --entity.remainTime);

	//�c�莞�Ԃ�0�ɂȂ�����I��
	if (entity.remainTime == 0)
	{
		if (level == 0)
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::City, 0.1f, 30, true);
		}
		else if (level == 1)
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::World, 0.1f, 30, true);
		}
		else
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::Space, 0.1f, 30, true);
		}
		//entity.field->SetScore();
		entity.field->SetResultPara();
		entity.ChangeState(State::Finish);
	}
	//AI���W���x�����ő�ɓ��B���Ă����烌�x���A�b�v
	else if (entity.field->ShouldLevelUp())
	{
		if (level == 0)
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::City, 0.1f, 30, true);
			entity.ChangeState(State::LevelUp);
		}
		else if (level == 1)
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::World, 0.1f, 30, true);
			entity.ChangeState(State::LevelUp);
		}
		else
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::Space, 0.1f, 30, true);
			entity.ChangeState(State::Result);
		}
	}
	//���i���[�h�ւ̑J�ڊm�F
	else if (entity.field->ShouldSwicthCamera())
	{
		entity.ChangeState(State::FarView);
	}

	//�J��������]�����邩
	if (entity.field->ShouldRotateCamera())
	{
		entity.fieldCamera->ChangeMode(FieldCamera::AngleRotate);
	}

	return State::Idle;
}

/**************************************
���ꏈ��
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{
	// �J�����̏œ_���Z�b�g
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);


	// �Q�[���V�[���Ŏg�p����UI�̕`���ON
	entity.field->SetViewerActive(true);
	entity.gameViewer->SetActive(true);
	GuideViewer::Instance()->SetActive(true);
	//entity.guideViewer->SetActive(true);

	// �g�p���Ȃ�UI�̕`���OFF�i�^�C�g���A���U���g�p�Ȃǁj
	entity.titleViewer->SetActive(false);
}
