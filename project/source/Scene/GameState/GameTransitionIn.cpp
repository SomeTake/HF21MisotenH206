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

	//�A�N�^�[�؂�ւ�

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
		entity.guideViewer->SetActive(false);
		entity.field->SetViewerActive(false);
		entity.gameViewer->SetGradeTitle(entity.level, [&]()
		{
			entity.guideViewer->SetActive(true);
			entity.field->SetViewerActive(true);
			entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);
			entity.ChangeState(GameScene::Idle);
		});
	}

	return GameScene::TransitionIn;
}
