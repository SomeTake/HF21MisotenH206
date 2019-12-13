//=====================================
//
//GameLevelUp.cpp
//�@�\:�Q�[���V�[�����x���A�b�v�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameLevelUp.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Field/FieldController.h"
#include "../../Event/EventController.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameLevelUp::OnStart(GameScene & entity)
{
	// �X�R�A�̉��Z
	entity.field->SetScore();

	//�X�e�b�v��������
	entity.step = Step::WaitLevelPopup;
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameLevelUp::OnUpdate(GameScene & entity)
{
	//�X�e�b�v���s
	switch (entity.step)
	{
	case Step::WaitLevelPopup:
		//�����N���x���|�b�v�A�b�v��҂K�v���Ȃ��Ȃ����牉�o�J�n
		if (!entity.field->ShouldWaitPopup())
		{
			// �O���[�h�A�b�v
			entity.gameViewer->SetGradeUp([&]()
			{
				//���x���A�b�v����
				entity.OnLevelUp();
				entity.ChangeState(GameScene::State::TransitionOut);
			});

			entity.step = Step::TelopIn;
		}

	default:
		break;
	}


	//�I�u�W�F�N�g�X�V
	entity.field->UpdateObject();
	entity.eventController->UpdateViewer();
	return State::LevelUp;
}
