//=====================================
//
// �Q�[���^�C�g��[GameTitle.cpp]
// �@�\�F�^�Ct�����
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GameTitle.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/TitleScene/TitleViewer.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	//�^�C�g���A�I�����ȂǂȂ�
	// �^�C�g����ʂŎg�p����UI�̕`���ON
	entity.titleViewer->SetActive(true);

	// �g�p���Ȃ�UI�̕`���OFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	entity.guideViewer->SetActive(false);
}

//=====================================
// �X�V����
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
	//���͂Ƃ肠�������������

	// �V�[���`�F���W
	if (entity.titleViewer->CheckSceneChange())
	{
		entity.titleViewer->SetNextScene(entity);
	}

	State next = State::Title;
	return next;
}
