//=====================================
//
//GameTransitionOut.cpp
//�@�\:�Q�[���̃��x���A�b�v�J�ڃX�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameTransitionOut.h"

#include "../../Field/Camera/FieldCamera.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Effect/GameParticleManager.h"
#include "../../Event/EventController.h"
#include "../../Field/FieldController.h"
#include "../../Booth/BoothController.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameTransitionOut::OnStart(GameScene & entity)
{
	//�J�����̏�Ԃ�J��
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionOut);

	entity.cntFrame = 0;

	SE::Play(SoundConfig::SEID::Transition, 0.4f);

	//gamaeViewer���I�t��
	entity.gameViewer->SetActive(false, GameViewer::ViewerNo::ItemStock);
	entity.gameViewer->SetActive(false, GameViewer::ViewerNo::Timer);
	entity.gameViewer->SetActive(false, GameViewer::ViewerNo::Level);

	GuideViewer::Instance()->SetData("�t�B�[���hLv���オ��܂�", GuideActor::AnimState::Cheering, SoundConfig::SEID::FieldLevelUp);
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameTransitionOut::OnUpdate(GameScene & entity)
{
	entity.cntFrame++;

	entity.eventController->UpdateViewer();
	entity.field->UpdateObject();

	//�_�p�[�e�B�N������
	if (entity.cntFrame == 45)
	{
		if (!entity.InTutorial)
		{
			BoothController::Instance()->RotateTable(GameScene::AngleTable[level]);
		}
		GameParticleManager::Instance()->Generate(GameParticle::Cloud, Vector3::Zero);
	}

	//�J��
	if (entity.cntFrame == 90)
	{
		entity.ChangeState(GameScene::TransitionIn);
	}

	return State::TransitionOut;
}
