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
#include "../../Viewer/GameScene/Controller/NameEntryViewer.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Network/UDPClient.h"
#include "../../../Framework/Task/TaskManager.h"

#include "../../Field/FieldController.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	entity.step = 0;

	// �ŉ��ʂ̃X�R�A���擾
	entity.Client->GetLastScore();

	//�X�R�A�\���A���O���͂ȂǂȂ�
	// �J�����̃��[�h�؂�ւ�
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	// ���U���g��ʂŎg�p����UI�̕`���ON(�l�[���G���g���[�͍ŏ��̓I�t�j
	entity.resultViewer->SetActive(true);

	// �g�p���Ȃ�UI�̕`���OFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	entity.nemeEntryViewer->SetActive(false);
	GuideViewer::Instance()->SetActive(false);
	//entity.guideViewer->SetActive(false);

	//�F�����x���̃X�R�A��ۑ�
	if (level == 2)
	{
		entity.field->SetScore();
	}

	// ���U���g�p��UI��AI���W���x����n��
	int cityScore = (int)entity.field->GetScore(Field::FieldLevel::City);
	int worldScore = (int)entity.field->GetScore(Field::FieldLevel::World);
	int spaceScore = (int)entity.field->GetScore(Field::FieldLevel::Space);
	entity.resultViewer->ReceiveParam(cityScore, worldScore, spaceScore);

	//�S�̃X�R�A���v�Z
	entity.entiretyScore = (int)(powf(10, 8) * spaceScore) + (int)(powf(10, 4) * worldScore) + cityScore;
}

//=====================================
// �X�V����
//=====================================
GameScene::State GameScene::GameResult::OnUpdate(GameScene & entity)
{
	// �N���C�A���g�X�V
	entity.Client->Update();

	//���W�b�N�ȊO���X�V
	entity.field->UpdateObject();

	switch (entity.step)
	{
	case Step::ScoreViewerIn:
		if (entity.resultViewer->IsPlayingAnimation() != ResultViewer::PlayingIn)
		{
			entity.step = Step::InputWait;
		}
		break;

	case Step::InputWait:
		if (Keyboard::GetTrigger(DIK_RETURN))
		{
			//�����L���O�X�V����������l�[���G���g���[��
			long long lastScore = entity.Client->GetLastScore();
			if (entity.entiretyScore > lastScore)
			{
				entity.nemeEntryViewer->SetActive(true);
				entity.step = Step::NameEntryWait;
			}
			//����ȊO�͒B�����ѕ\���֑J��
			else
			{
				entity.step = Step::NameEntryFinish;
			}
		}
		break;

	case Step::NameEntryWait:
		//TODO:�l�[���G���g���[�̏I�����R�[���o�b�N�Ŏ󂯎��悤�ɂ���
		entity.step = Step::NameEntryFinish;
		break;

	case Step::NameEntryFinish:
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
		break;

	default:
		break;
	}


	return State::Result;
}
