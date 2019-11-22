//=====================================
//
//GameTransition.cpp
//�@�\:�Q�[���̃��x���A�b�v�J�ڃX�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameTransition.h"

#include "../../Field/Camera/FieldCamera.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Effect/GameParticleManager.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameTransition::OnStart(GameScene & entity)
{
	//�J�����̏�Ԃ�J��
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionOut);
	
	//�_�p�[�e�B�N������
	TaskManager::Instance()->CreateDelayedTask(60, [&]()
	{
		GameParticleManager::Instance()->Generate(GameParticle::Cloud, Vector3::Zero);
	});
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameTransition::OnUpdate(GameScene & entity)
{
	return State::Transition;
}
