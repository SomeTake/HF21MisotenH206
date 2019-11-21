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

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	//�X�R�A�\���A���O���͂ȂǂȂ�
	// ���U���g��ʂŎg�p����UI�̕`���ON

	// �g�p���Ȃ�UI�̕`���OFF
	entity.field->SetActive(false);
	entity.gameViewer->SetActive(false);
	entity.guideViewer->SetActive(false);

	// ���U���g�p��UI��AI���W���x����n��
	// entity.resultScore->SetScore(entity.field->GetScore());

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