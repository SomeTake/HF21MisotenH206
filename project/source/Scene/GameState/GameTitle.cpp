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
#include "../../Viewer/TutorialScene/TutorialViewer.h"
#include "../../Event/EventController.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Serial/SerialWrapper.h"
#include "../../Sound/PlayBGM.h"
#include "../../Booth/BoothController.h"
#include "../../Reward/RewardNotifier.h"
#include "../../Reward/RewardController.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Tool/DebugWindow.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	// �V�[���`�F���W
	entity.enableInput = false;
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]
	{
		entity.enableInput = true;
	});

	// ���т̃��Z�b�g
	// �����[�h�����Z�b�g
	entity.rewardNotifier->ResetAchieved();
	RewardController::Instance()->ResetAllRewardData();

	// �J�����̃��[�h�ؑ�
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	// �^�C�g����ʂŎg�p����UI�̕`���ON
	//entity.titleViewer->SetActive(true);
	entity.titleViewer->Reset();

	// �g�p���Ȃ�UI�̕`���OFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	GuideViewer::Instance()->SetActive(false);
	entity.resultViewer->SetActive(false);
	entity.nameEntryViewer->SetActive(false);
	entity.eventController->ClearEventViewer();
	entity.tutorialViewer->SetActive(false);

	// �^�C�g����BGM���J�n
	PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::Title, SoundConfig::VolumeBGM, 30, false);

	//���[�^�̊p�x��������
	BoothController::Instance()->RotateTable(GameScene::AngleTable[0]);

	entity.step = 0;
	entity.InTutorial = false;
	SelectedFlag = false;
}

//=====================================
// �X�V����
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
#if _DEBUG
	static bool SkipTutorial = false;
	Debug::Begin("DebugTool");
	Debug::CheckBox("SkipTutorial", SkipTutorial);
	Debug::End();
#endif

	entity.field->UpdateObject();

	if (!entity.enableInput)
		return State::Title;

	if (entity.step == 1)
	{
		// �����[�h�m�F��ʂ���X�e�b�v��߂�
		if (entity.titleViewer->GetRewardViewer())
		{
			if (Keyboard::GetTrigger(DIK_X) || GamePad::GetTrigger(0, BUTTON_X))
			{
				entity.step = 0;
			}
		}

		return State::Title;
	}

	if ((Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C)) && !SelectedFlag)
	{
		TitleViewer::MenuID selected = entity.titleViewer->GetSelectedMenu();

		// �V�[���`�F���W
		if (selected == TitleViewer::MenuID::StartGame)
		{
			entity.remainTime = 30 * 180;
			entity.step++;
			SelectedFlag = true;

			TaskManager::Instance()->CreateDelayedTask(30, [&]()
			{
				entity.titleViewer->SetActive(false);
#if _DEBUG
				if (!SkipTutorial)
				{
					TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
					{
						entity.level = 0;
						entity.Clear();
						entity.SetTutorial();
						entity.field->Load(entity.csvNo);

						// �J�����̏œ_���Z�b�g
						entity.fieldCamera->InitRotatedAngle();
						entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
						entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

						// �V�[���`�F���W
						TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]()
						{
							entity.gameViewer->SetActive(true);

							// �O���[�h�^�C�g��
							entity.gameViewer->SetGradeTitle(3, [&]()
							{
								GuideViewer::Instance()->SetData("����؂��čs���܂��傤", GuideActor::AnimState::TalkingTypeA, SoundConfig::SEID::GameStart);
								entity.ChangeState(GameScene::State::Tutorial);
							});
						});
					});
				}
				else
				{

					TaskManager::Instance()->CreateDelayedTask(30, [&]() 
					{
						entity.titleViewer->SetActive(false);

						entity.gameViewer->SetActive(true);
						entity.gameViewer->SetActive(false, GameViewer::ViewerNo::ItemStock);
						entity.gameViewer->SetActive(false, GameViewer::ViewerNo::Timer);
						entity.gameViewer->SetActive(false, GameViewer::ViewerNo::Level);

						entity.gameViewer->SetGradeTitle(0, [&]()
						{
							entity.gameViewer->SetActive(true, GameViewer::ViewerNo::ItemStock);
							entity.gameViewer->SetActive(true, GameViewer::ViewerNo::Timer);
							entity.gameViewer->SetActive(true, GameViewer::ViewerNo::Level);
							entity.fieldCamera->InitRotatedAngle();

							GuideViewer::Instance()->SetData("����؂��čs���܂��傤", GuideActor::AnimState::TalkingTypeA, SoundConfig::SEID::GameStart);
							entity.ChangeState(GameScene::State::Idle);
						});
					});
				}
#else
				TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
				{
					entity.level = 0;
					entity.Clear();
					entity.SetTutorial();
					entity.field->Load(entity.csvNo);

					// �J�����̏œ_���Z�b�g
					entity.fieldCamera->InitRotatedAngle();
					entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
					entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

					PlayBGM::Instance()->FadeOut();
					PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::Tutorial, 0.5f, 60, false);

					// �V�[���`�F���W
					TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]()
					{
						entity.gameViewer->SetActive(true);

						// �O���[�h�^�C�g��
						entity.gameViewer->SetGradeTitle(3, [&]()
						{
							GuideViewer::Instance()->SetData("����؂��čs���܂��傤", GuideActor::AnimState::TalkingTypeA, SoundConfig::SEID::GameStart);
							entity.ChangeState(GameScene::State::Tutorial);
						});
					});
				});
#endif
			});
		}
		else if (selected == TitleViewer::MenuID::ViewReward)
		{
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				entity.titleViewer->SetRewardViewer();
				entity.titleViewer->Reset();
			});
		}
		else if (selected == TitleViewer::QuitGame)
		{
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				PostQuitMessage(0);
			});
		}

		if (selected != TitleViewer::None)
		{
			SE::Play(SoundConfig::SEID::Select01, 0.5f);
		}
	}

	State next = State::Title;
	return next;
}
