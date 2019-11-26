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
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GamePause::OnStart(GameScene & entity)
{
	//NOTE:������FieldViewer���I�t�ɂ��Ă��܂��ƃ��x���A�b�v�������Ȃ��Ȃ�̂ł��Ȃ�
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GamePause::OnUpdate(GameScene & entity)
{
	//���W�b�N�ȊO���X�V
	entity.field->UpdateObject();

	//�|�b�v�A�b�v�I���̑ҋ@���̓C�x���g�̃I�u�W�F�N�g���X�V�����Ȃ�
	if (!entity.field->ShouldWaitPopup())
	{
		//�C�x���g����FieldViewer���I�t��
		//NOTE�F�������ǂƂ肠�������̂����ł���Ă��܂�
		entity.field->SetViewerActive(false);
		entity.gameViewer->SetActive(false);
		entity.guideViewer->SetActive(false);

		entity.eventController->Update();
	}

	//�C�x���g�r���[���X�V
	entity.eventController->UpdateViewer();

	//���f�����̓C�x���g�n���h�����ɔC����
	return State::Pause;
}
