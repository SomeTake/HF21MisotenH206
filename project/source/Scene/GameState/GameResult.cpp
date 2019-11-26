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
#include "../../Field/Camera/FieldCamera.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../Field/FieldController.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	//�X�R�A�\���A���O���͂ȂǂȂ�
	// �J�����̃��[�h�؂�ւ�
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	// ���U���g��ʂŎg�p����UI�̕`���ON
	entity.resultViewer->SetActive(true);

	// �g�p���Ȃ�UI�̕`���OFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	entity.guideViewer->SetActive(false);

	//�F�����x���̃X�R�A��ۑ�
	if (level == 2)
	{
		entity.field->SetScore();
	}

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
	//�Ƃ肠�����G���^�[�������ꂽ��^�C�g���֖߂�
	if (Keyboard::GetTrigger(DIK_RETURN))
	{
		TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
		{
			entity.level = 0;
			entity.Clear();
			entity.SetFieldLevel(0);
			entity.field->Load();
			entity.ChangeState(State::Title);
		});
	}

	return State::Result;
}
