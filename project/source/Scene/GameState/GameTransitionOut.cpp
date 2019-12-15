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

/**************************************
���ꏈ��
***************************************/
void GameScene::GameTransitionOut::OnStart(GameScene & entity)
{
	//�J�����̏�Ԃ�J��
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionOut);

	entity.cntFrame = 0;

	SE::Play(SoundConfig::SEID::Transition, 1.0f);
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
		BoothController::Instance()->RotateTable(GameScene::AngleTable[level]);
		GameParticleManager::Instance()->Generate(GameParticle::Cloud, Vector3::Zero);
	}

	//�J��
	if (entity.cntFrame == 90)
	{
		entity.ChangeState(GameScene::TransitionIn);
	}

	return State::TransitionOut;
}
