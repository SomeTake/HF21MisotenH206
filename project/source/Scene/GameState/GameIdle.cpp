//=====================================
//
//Template.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameIdle.h"
#include "../../Field/FieldController.h"

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	entity.field->Update();

	return State::Idle;
}

/**************************************
���ꏈ��
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
