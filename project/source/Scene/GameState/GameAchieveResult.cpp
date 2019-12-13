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
#include "../../Viewer/GameScene/Controller/NameEntryViewer.h"
#include "../../Viewer/NameViewer/Name.h"

#include <functional>

/**************************************
���ꏈ��
***************************************/
void GameScene::GameAchieveResult::OnStart(GameScene & entity)
{
	Debug::Log("AchieveResult is Started");

	auto rewardContainer = RewardController::Instance()->GetAllAchieved();

	//���т��Ȃ�������^�C�g���֑J��
	if (rewardContainer.empty())
	{
		TransitionToTitle(entity);
		entity.step = Step::Transition;
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
			if (RewardController::Instance()->ExistFirstAchieved())
			{
				// �܂����O�����͂���Ȃ�������
				if (!entity.nemeEntryViewer->GetNameEntered())
				{
					entity.nemeEntryViewer->SlideNameEntryViewer(true);
					entity.step = Step::AchieveNameEntryWait;
				}
				else
				{
					entity.step = Step::AchieveNameEntryFinish;
				}
			}
			//�Ȃ�������J�ڂ�
			else
			{
				entity.step = Step::AchieveNameEntryFinish;
			}
		}
		break;

	case Step::AchieveNameEntryWait:

		//���O���͂̏I���҂�
		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			entity.nemeEntryViewer->SlideNameEntryViewer(false);

			//�I��������J��
			entity.step = Step::AchieveNameEntryFinish;
		}
		break;

	case Step::AchieveNameEntryFinish:

		//�l�[����ۑ�
		RewardController::Instance()->SetFirstAchieverName(entity.nemeEntryViewer->GetEntryNameID());

		//�J��
		TransitionToTitle(entity);
		entity.step = Step::Transition;

		break;
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
}
