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
	//���͊m�F
	entity.field->CheckInput();
	entity.fieldCamera->CheckInput();

	//�e�I�u�W�F�N�g�X�V
	entity.field->UpdateLogic();
	entity.field->UpdateObject();

	//�C�x���g�X�V
	entity.eventController->Update();

	//�������ԃJ�E���g
	entity.remainTime = Math::Max(0, --entity.remainTime);

	//�c�莞�Ԃ�0�ɂȂ�����I��
	if (entity.remainTime == 0)
	{
		entity.ChangeState(State::Finish);
	}
	//AI���W���x�����ő�ɓ��B���Ă����烌�x���A�b�v
	else if (entity.field->ShouldLevelUp())
	{
		entity.ChangeState(State::LevelUp);
	}

	return State::Idle;
}

/**************************************
���ꏈ��
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
