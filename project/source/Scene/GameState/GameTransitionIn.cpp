//=====================================
//
//GameTransitionIn.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameTransitionIn.h"

#include "../../Field/Camera/FieldCamera.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameTransitionIn::OnStart(GameScene & entity)
{
	//�S�ăN���A
	entity.Clear();

	//�t�B�[���h���x���؂�ւ�


	//�}�b�v�ǂݍ���


	//�A�N�^�[�؂�ւ�


	//�J�����؂�ւ�
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionIn);

	entity.cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameTransitionIn::OnUpdate(GameScene & entity)
{
	entity.cntFrame++;

	if (entity.cntFrame == 90)
	{
		entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);
		entity.ChangeState(GameScene::Idle);
	}

	return GameScene::TransitionIn;
}
