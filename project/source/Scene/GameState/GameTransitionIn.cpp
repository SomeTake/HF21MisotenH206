//=====================================
//
//GameTransitionIn.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameTransitionIn.h"

#include "../../Field/Camera/FieldCamera.h"
#include "../../Field/FieldController.h"
#include "../../Event/EventController.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"

#include "../../../Framework/Tool/ProfilerCPU.h"
#include "../../../Framework/Tool/DebugWindow.h"

#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Task/TaskManager.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameTransitionIn::OnStart(GameScene & entity)
{
	//�S�ăN���A
	entity.Clear();

	//�t�B�[���h���x���؂�ւ�
	entity.SetFieldLevel(entity.level);

	//�}�b�v�ǂݍ���
	entity.field->Load();

	//BGM���N���X�t�F�[�h
	SoundConfig::BGMID bgmID = SoundConfig::GetBgmID(entity.level);
	PlayBGM::Instance()->FadeOut();
	PlayBGM::Instance()->FadeIn(bgmID, 0.3f, 90);

	entity.cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameTransitionIn::OnUpdate(GameScene & entity)
{
	entity.cntFrame++;

	entity.eventController->UpdateViewer();
	entity.field->UpdateObject();

	if (entity.cntFrame == 15)
	{
		//�J�����؂�ւ�
		entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionIn);
	}

	if (entity.cntFrame == 100)
	{
		GuideViewer::Instance()->SetActive(false);
		entity.field->SetViewerActive(false);

		entity.gameViewer->SetGradeTitle(entity.level, [&]()
		{
			GuideViewer::Instance()->SetActive(true);

			entity.field->SetViewerActive(true);
			entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

			entity.gameViewer->SetActive(true, GameViewer::ViewerNo::ItemStock);
			entity.gameViewer->SetActive(true, GameViewer::ViewerNo::Timer);
			entity.gameViewer->SetActive(true, GameViewer::ViewerNo::Level);

			entity.ChangeState(State::Idle);
		});
	}

	return GameScene::TransitionIn;
}
