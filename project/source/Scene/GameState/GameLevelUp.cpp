//=====================================
//
//GameLevelUp.cpp
//�@�\:�Q�[���V�[�����x���A�b�v�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameLevelUp.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameLevelUp::OnStart(GameScene & entity)
{
	//TODO:���x���A�b�v���̉��o���Đ�����
	// �X�R�A�̉��Z
	entity.field->SetScore();

	//�{���͉��o�I���̃R�[���o�b�N�őJ�ڂ�����

	// �O���[�h�A�b�v
	entity.gameViewer->SetGradeUp([&]()
	{
		//���x���A�b�v����
		entity.OnLevelUp();
		entity.ChangeState(GameScene::State::TransitionOut);
	});

	SE::Play(SoundConfig::SEID::FieldLevelUp, 1.0f);
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameLevelUp::OnUpdate(GameScene & entity)
{
	return State::LevelUp;
}
