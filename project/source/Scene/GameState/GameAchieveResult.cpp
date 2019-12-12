//=====================================
//
//GameAchieveResult.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
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

#include <functional>

/**************************************
���ꏈ��
***************************************/
void GameScene::GameAchieveResult::OnStart(GameScene & entity)
{
	Debug::Log("AchieveResult is Started");

	auto rewardContainer = RewardController::Instance()->IsAllAchieved();

	//���т��Ȃ�������^�C�g���֑J��
	if (rewardContainer.empty())
	{
		TransitionToTitle(entity);
	}
	//��������\���J�n
	else
	{
		entity.resultViewer->SetAchieveViewerActive(true);
		entity.resultViewer->SetAchiveViewer(rewardContainer, [&]()
		{
			entity.step++;
		});
		entity.step = Step::AchieveViewerIn;
	}
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameAchieveResult::OnUpdate(GameScene & entity)
{
	//���W�b�N�ȊO���X�V
	entity.field->UpdateObject();

	switch (entity.step)
	{
	case Step::AchieveViewerIn:

		break;

	case Step::AchieveInputWait:
		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			//���B���̎��т���������l�[���G���g���[
			if (RewardController::Instance()->FindFirstAchieved())
			{
				entity.step = Step::AchieveInputWait;
			}
			//�Ȃ�������^�C�g����
			else
			{
				TransitionToTitle(entity);
			}
		}
	}

	return State::AchieveResult;
}

/**************************************
�^�C�g���֑J��
***************************************/
void GameScene::GameAchieveResult::TransitionToTitle(GameScene& entity)
{
	PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::Result, 0.1f, 30, true);

	TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
	{
		entity.level = 0;
		entity.Clear();
		entity.SetFieldLevel(0);
		entity.field->Load();
		entity.ChangeState(State::Title);
	});

	entity.step = Transition;
}
