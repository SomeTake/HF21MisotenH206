//=====================================
//
//GameAchieveResult.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameAchieveResult.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../Reward/RewardController.h"
#include "../../Field/FieldController.h"

#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Input/input.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"
#include "../../Viewer/GameScene/Controller/NameEntryViewer.h"
#include "../../Viewer/NameViewer/Name.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

#include <functional>

/**************************************
入場処理
***************************************/
void GameScene::GameAchieveResult::OnStart(GameScene & entity)
{
	Debug::Log("AchieveResult is Started");

	auto rewardContainer = RewardController::Instance()->GetAllAchieved();

	//実績がなかったらタイトルへ遷移
	if (rewardContainer.empty())
	{
		TransitionToTitle(entity);
		entity.step = Step::Transition;
	}
	//あったら表示開始
	else
	{
		SE::Play(SoundConfig::SEID::Clap, 0.5f);
		if (RewardController::Instance()->ExistFirstAchieved())
		{
			SE::Play(SoundConfig::SEID::NewReward, SoundConfig::VolumeVoice);
		}

		entity.resultViewer->SetAchieveViewerActive(true);
		entity.resultViewer->SetAchiveViewer(rewardContainer, [&]()
		{
			entity.step++;
		});
		entity.step = Step::AchieveViewerIn;
	}
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameAchieveResult::OnUpdate(GameScene & entity)
{
	//ロジック以外を更新
	entity.field->UpdateObject();

	switch (entity.step)
	{
	case Step::AchieveViewerIn:

		break;

	case Step::AchieveInputWait:

		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			//初達成の実績があったらネームエントリー
			if (RewardController::Instance()->ExistFirstAchieved())
			{
				// まだ名前が入力されなかったら
				if (!entity.nameEntryViewer->GetNameEntered())
				{
					entity.nameEntryViewer->SlideNameEntryViewer(true);
					entity.step = Step::AchieveNameEntryWait;
				}
				else
				{
					entity.step = Step::AchieveNameEntryFinish;
				}
			}
			//なかったら遷移へ
			else
			{
				entity.step = Step::AchieveNameEntryFinish;
			}
		}
		break;

	case Step::AchieveNameEntryWait:

		//名前入力の終了待ち
		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			entity.nameEntryViewer->SlideNameEntryViewer(false);

			//終了したら遷移
			entity.step = Step::AchieveNameEntryFinish;
		}
		break;

	case Step::AchieveNameEntryFinish:

		//ネームを保存
		RewardController::Instance()->SetFirstAchieverName(entity.nameEntryViewer->GetEntryNameID());

		//遷移
		TransitionToTitle(entity);
		entity.step = Step::Transition;

		break;
	}

	return State::AchieveResult;
}

/**************************************
タイトルへ遷移
***************************************/
void GameScene::GameAchieveResult::TransitionToTitle(GameScene& entity)
{
	PlayBGM::Instance()->FadeOut();

	TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
	{
		entity.level = 0;
		entity.csvNo = rand() % entity.CsvFileMax;
		entity.Clear();
		entity.SetFieldLevel(0);
		entity.field->Load(entity.csvNo);
		entity.ChangeState(State::Title);
	});
}
