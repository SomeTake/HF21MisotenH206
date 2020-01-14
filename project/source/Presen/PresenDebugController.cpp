//=====================================
//
//PresenDebugController.cpp
//�@�\:�v���[���p�̃f�o�b�O����N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PresenDebugController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Input/Gamepad.h"
#include "../../Framework/Input/Keyboard.h"

#include "../Event/EventController.h"
#include "../Event/EventBase.h"
#include "../Event/MinusEvent/CityDestroyEvent.h"
#include "../Viewer/GameScene/Controller/EventViewer.h"

#include "../Field/FieldController.h"

/**************************************
�R���X�g���N�^
***************************************/
PresenDebugController::PresenDebugController(GameScene * scene) :
	scene(scene)
{
}

/**************************************
�f�X�g���N�^
***************************************/
PresenDebugController::~PresenDebugController()
{
}

/**************************************
�X�V����
***************************************/
void PresenDebugController::Update()
{
	return;

	//X�{�^����AI���x������
	if (GamePad::GetTrigger(0, BUTTON_B))
	{
		_DecreaseLevelAI();
	}
	//L1�{�^����覐Ώ���
	//if (GamePad::GetTrigger(0, BUTTON_Y))
	//{
	//	_RaiseMeteorEvent();
	//}
	//L2�{�^���ŋ������x���A�b�v
	if (GamePad::GetTrigger(0, BUTTON_L))
	{
		_ForceLevelUp();
	}
	//R2�{�^���ŋ����^�C���A�b�v
	if (GamePad::GetTrigger(0, BUTTON_R))
	{
		_ForceTimeUp();
	}

	//X�{�^����AI���x������
	if (Keyboard::GetPress(DIK_LCONTROL) && Keyboard::GetTrigger(DIK_1))
	{
		_DecreaseLevelAI();
	}
	//L1�{�^����覐Ώ���
	if (Keyboard::GetPress(DIK_LCONTROL) && Keyboard::GetTrigger(DIK_2))
	{
		_RaiseMeteorEvent();
	}
	//L2�{�^���ŋ������x���A�b�v
	if (Keyboard::GetPress(DIK_LCONTROL) && Keyboard::GetTrigger(DIK_3))
	{
		_ForceLevelUp();
	}
	//R2�{�^���ŋ����^�C���A�b�v
	if (Keyboard::GetPress(DIK_LCONTROL) && Keyboard::GetTrigger(DIK_4))
	{
		_ForceTimeUp();
	}

}

/**************************************
覐΃C�x���g��������
***************************************/
void PresenDebugController::_RaiseMeteorEvent()
{
	if (scene->currentState != GameScene::Idle)
		return;

	EventController *controller = scene->eventController;
	EventBase *ptr = new CityDestroyEvent(controller->eventViewer, controller->beatViewer, controller->camera);

	controller->eventViewer->SetEventMessage(ptr->GetEventMessage(scene->level));
	controller->EventVec.push_back(ptr);

	scene->ChangeState(GameScene::Pause);
}

/**************************************
�������x���A�b�v
***************************************/
void PresenDebugController::_ForceLevelUp()
{
	if (scene->currentState != GameScene::Idle)
		return;

	Field::FieldController *controller = scene->field;
	controller->developmentLevelAI = 9999.0f;

	//controller->SetScore();
	controller->SetResultPara();
	scene->ChangeState(GameScene::LevelUp);
}

/**************************************
AI���x������
***************************************/
void PresenDebugController::_DecreaseLevelAI()
{
	if (scene->currentState != GameScene::Idle)
		return;

	Field::FieldController *controller = scene->field;
	controller->developmentLevelAI = 0.0f;
}

/**************************************
�����^�C���A�b�v
***************************************/
void PresenDebugController::_ForceTimeUp()
{
	if (scene->currentState != GameScene::Idle)
		return;

	scene->remainTime = 0;
}
