//=====================================
//
//GamePause.cpp
//�@�\:�Q�[�����f�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GamePause.h"
#include "../../Event/EventController.h"
#include "../../Field/FieldController.h"

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
	//���W�b�N�ȊO���X�V
	entity.field->UpdateObject();

	//�|�b�v�A�b�v�I���̑ҋ@���̓C�x���g���X�V�����Ȃ�
	if (!entity.field->ShouldWaitPopup())
	{
		entity.eventController->Update();
	}

	//���f�����̓C�x���g�n���h�����ɔC����
	return State::Pause;
}
