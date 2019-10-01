//=====================================
//
//�^�X�N����[Task.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Task.h"

/**************************************
�}�N����`
***************************************/

/**************************************
Task�R���X�g���N�^
***************************************/
Task::Task(const std::function<void(void)>& func) :
	func(func),
	state(State::Idle)
{

}

/**************************************
Task�f�X�g���N�^
***************************************/
Task::~Task()
{
	int a = 1 + 1;
}

/**************************************
Task��~����
***************************************/
void Task::Stop()
{
	state = State::Finished;
}

/**************************************
Task�ĊJ����
***************************************/
void Task::Resume()
{
	state = State::Idle;
}

/**************************************
Task���f����
***************************************/
void Task::Pause()
{
	state = State::Paused;
}

/**************************************
Task�R���X�g���N�^
***************************************/
bool Task::IsFinished()
{
	return state == State::Finished;
}