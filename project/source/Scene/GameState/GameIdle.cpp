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
#include "../../Event/EventController.h"

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	State next = State::Idle;

	//���͊m�F
	entity.field->CheckInput();
	entity.fieldCamera->CheckInput();

	//�e�I�u�W�F�N�g�X�V
	entity.field->Update();

	//�C�x���g�X�V
	entity.eventController->Update();

	//�c�莞�Ԃ�0�ɂȂ�����I��
	if (!entity.field->IsTimeRemaining())
	{
		next = State::Finish;
	}
	//AI���W���x�����ő�ɓ��B���Ă����烌�x���A�b�v
	else if (entity.field->ShouldLevelUp())
	{
		next = State::LevelUp;
	}

	return next;
}

/**************************************
���ꏈ��
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
