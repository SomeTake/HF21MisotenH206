//=====================================
//
//GameLevelUp.cpp
//�@�\:�Q�[���V�[�����x���A�b�v�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameLevelUp.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameLevelUp::OnStart(GameScene & entity)
{
	//TODO:���x���A�b�v���̉��o���Đ�����
	//�{���͉��o�I���̃R�[���o�b�N�őJ�ڂ�����

	//���x���A�b�v����
	entity.OnLevelUp();

	entity.ChangeState(GameScene::State::TransitionOut);
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameLevelUp::OnUpdate(GameScene & entity)
{
	return State::LevelUp;
}
