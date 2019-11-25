//=====================================
//
// �Q�[�����U���g[GameResult.cpp]
// �@�\�F���U���g���
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GameResult.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	//�X�R�A�\���A���O���͂ȂǂȂ�
	// ���U���g��ʂŎg�p����UI�̕`���ON
	entity.resultViewer->SetActive(true);

	// �g�p���Ȃ�UI�̕`���OFF
	entity.field->SetActive(false);
	entity.gameViewer->SetActive(false);
	entity.guideViewer->SetActive(false);

	//// ���U���g�p��UI��AI���W���x����n��
	int cityScore = (int)entity.field->GetScore(Field::FieldLevel::City);
	int worldScore = (int)entity.field->GetScore(Field::FieldLevel::World);
	int spaceScore = (int)entity.field->GetScore(Field::FieldLevel::Space);
	entity.resultViewer->ReceiveParam(cityScore, worldScore, spaceScore);
}

//=====================================
// �X�V����
//=====================================
GameScene::State GameScene::GameResult::OnUpdate(GameScene & entity)
{
	//���͂Ƃ肠�������������
	State next = State::Result;
	return next;
}
