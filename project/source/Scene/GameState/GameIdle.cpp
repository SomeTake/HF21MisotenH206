//=====================================
//
//Template.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameIdle.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	//���͊m�F
	entity.field->CheckInput();
	entity.fieldCamera->CheckInput();

	//�J�����X�V
	entity.fieldCamera->Update();

	//�e�I�u�W�F�N�g�X�V
	entity.field->Update();

	//�������Ԃ̍X�V
	entity.remainTime--;

	return State::Idle;
}

/**************************************
���ꏈ��
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
