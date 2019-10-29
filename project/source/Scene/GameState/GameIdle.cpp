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
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Tool/ProfilerCPU.h"

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	//���͊m�F
	entity.field->CheckInput();

	//�t�B�[���h�X�V
	ProfilerCPU::Instance()->Begin("Update Logic");
	entity.field->UpdateLogic();
	ProfilerCPU::Instance()->End("Update Logic");

	ProfilerCPU::Instance()->Begin("Update FieldObject");
	entity.field->UpdateObject();
	ProfilerCPU::Instance()->End("Update FieldObject");

	//�C�x���g�X�V
	ProfilerCPU::Instance()->Begin("Update Event");
	entity.eventController->Update();
	ProfilerCPU::Instance()->End("Update Event");

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
	//���i���[�h�ւ̑J�ڊm�F
	else if (Keyboard::GetTrigger(DIK_SPACE))
	{
		entity.ChangeState(State::FarView);
	}

	return State::Idle;
}

/**************************************
���ꏈ��
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
