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
#include "../../Event/EventController.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Network/UDPClient.h"
#include "../../../Framework/Task/TaskManager.h"

#include "../../Field/FieldController.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	entity.step = 0;

	//�X�R�A�\���A���O���͂ȂǂȂ�
	// �J�����̃��[�h�؂�ւ�
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	// ���U���g��ʂŎg�p����UI�̕`���ON(�l�[���G���g���[�͍ŏ��̓I�t�j
	entity.resultViewer->SetActive(true);
	entity.resultViewer->SlideScoreViewer(true);
	entity.resultViewer->SetAchieveViewerActive(false);

	// �l�[���G���g���[�̏�����
	entity.nameEntryViewer->Init();

	// �g�p���Ȃ�UI�̕`���OFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	entity.nameEntryViewer->SetActive(false);
	entity.eventController->ClearEventMessage();
	GuideViewer::Instance()->SetActive(false);
	//entity.guideViewer->SetActive(false);

	//�F�����x���̃X�R�A��ۑ�
	if (level == 2)
	{
		entity.field->SetResultPara();
	}

	// ���U���g�p��UI�Ƀp�����[�^��n��
	ResultViewerParam* Prarm = entity.field->GetResultPara();
	entity.resultViewer->ReceiveParam(*Prarm);

	SE::Play(SoundConfig::SEID::FinishME, 0.5f);
	PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::Result, SoundConfig::VolumeBGM, 300, false);

	//�S�̃X�R�A���v�Z
	string TotalScore = std::to_string(Prarm->score[Field::FieldLevel::Space]) +
		std::to_string(Prarm->score[Field::FieldLevel::World]) +
		std::to_string(Prarm->score[Field::FieldLevel::City]);
	entity.entiretyScore = std::stoull(TotalScore);

	//�����L���O�X�V����������l�[���G���g���[��
	entity.ShowNameEntry = entity.entiretyScore > entity.Client->GetLastScore() ? true : false;
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
			entity.step = Step::ScoreInputWait;
		}
		break;

	case Step::ScoreInputWait:
		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			//�����L���O�X�V����������l�[���G���g���[��
			if (entity.ShowNameEntry)
			{
				SE::Play(SoundConfig::SEID::NewRecord, SoundConfig::VolumeVoice);
				entity.nameEntryViewer->SlideNameEntryViewer(true);
				entity.step = Step::ScoreNameEntryWait;
			}
			//����ȊO�͒B�����ѕ\���֑J��
			else
			{
				entity.resultViewer->SlideScoreViewer(false);
				entity.step = Step::ScoreViewerOut;
			}
		}
		break;

	case Step::ScoreNameEntryWait:

		//�G���^�[�L�[�Ńl�[���G���g���[�I��
		//if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		entity.step = Step::ScoreNameEntryFinish;
		break;

	case Step::ScoreNameEntryFinish:

		//�G���^�[�L�[�������ꂽ��X�R�A�r���[�����X���C�h�A�E�g������
		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			entity.resultViewer->SlideScoreViewer(false);
			entity.nameEntryViewer->SlideNameEntryViewer(false);
			entity.step = Step::ScoreViewerOut;
			SE::Play(SoundConfig::SEID::NewReward, SoundConfig::VolumeVoice);

			// �T�[�o�[�Ƀ����L���O�p�P�b�g�𑗐M
			entity.Client->SendRankPacket(entity.nameEntryViewer->GetEntryNameID(), entity.entiretyScore);
		}
		break;

	case Step::ScoreViewerOut:
		if (entity.resultViewer->IsPlayingAnimation() != ResultViewer::PlayingOut)
		{
			entity.nameEntryViewer->SetActive(false);
			entity.ChangeState(State::AchieveResult);
		}
		break;

	default:

		break;
	}


	return State::Result;
}
