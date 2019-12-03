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
#include "../../Field/Camera/FieldCamera.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../Viewer/GameScene/Controller/NameEntryViewer.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Serial/SerialWrapper.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	// �V�[���`�F���W
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop);

	// �J�����̃��[�h�ؑ�
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	//�^�C�g���A�I�����ȂǂȂ�
	// �^�C�g����ʂŎg�p����UI�̕`���ON
	entity.titleViewer->SetActive(true);

	// �g�p���Ȃ�UI�̕`���OFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	entity.guideViewer->SetActive(false);
	entity.resultViewer->SetActive(false);
	entity.nemeEntryViewer->SetActive(false);

	//���[�^�̊p�x��������
	entity.serial->Write(GameScene::AngleTable[0]);
}

//=====================================
// �X�V����
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
	entity.field->UpdateObject();

	// �V�[���`�F���W
	if (entity.titleViewer->CheckSceneChange())
	{
		entity.titleViewer->SetNextScene(entity);
	}

	State next = State::Title;
	return next;
}
