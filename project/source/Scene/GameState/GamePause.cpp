//=====================================
//
//GamePause.cpp
//�@�\:�Q�[�����f�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GamePause.h"
#include "../../Event/EventController.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GamePause::OnStart(GameScene & entity)
{

}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GamePause::OnUpdate(GameScene & entity)
{
	//�C�x���g�̂ݍX�V
	entity.eventController->Update();

	//���f�����̓C�x���g�n���h�����ɔC����
	return State::Pause;
}
