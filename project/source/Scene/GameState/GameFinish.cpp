//=====================================
//
//GameFinish.cpp
//�@�\:�Q�[���V�[���I������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameFinish.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Field/FieldController.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameFinish::OnStart(GameScene & entity)
{
	SE::Play(SoundConfig::SEID::TimeUp, 1.0f);
	//�^�C���A�b�v�\���A�\�����I������烊�U���g�֑J��
	entity.gameViewer->SetTimeUp([&]()
	{
		entity.ChangeState(GameScene::State::Result);
	});
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameFinish::OnUpdate(GameScene & entity)
{
	//���W�b�N�ȊO���X�V
	entity.field->UpdateObject();

	State next = State::Finish;
	return next;
}
