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
	ProfilerCPU::Instance()->Begin("Update Event");
	entity.eventController->Update();
	entity.eventController->UpdateViewer();
	ProfilerCPU::Instance()->End("Update Event");

	//���͊m�F
	entity.field->CheckInput();

	//�t�B�[���h�X�V
	ProfilerCPU::Instance()->Begin("Update Logic");
	entity.field->UpdateLogic();
	ProfilerCPU::Instance()->End("Update Logic");

	ProfilerCPU::Instance()->Begin("Update FieldObject");
	entity.field->UpdateObject();
	ProfilerCPU::Instance()->End("Update FieldObject");

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
	else if (entity.field->ShouldSwicthCamera())
	{
		entity.ChangeState(State::FarView);
	}

	//�J��������]�����邩
	if (entity.field->ShouldRotateCamera())
	{
		entity.fieldCamera->ChangeMode(FieldCamera::AngleRotate);
	}

	return State::Idle;
}

/**************************************
���ꏈ��
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
