//=============================================================================
//
// �|�[�Y��ʃN���X [GameInterrupt.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "GameInterrupt.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/TitleScene/TitleViewer.h"
#include "../../Viewer/TutorialScene/TutorialViewer.h"
#include "../../Reward/RewardController.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Tween/Tween.h"


/**************************************
���ꏈ��
***************************************/
void GameScene::GameInterrupt::OnStart(GameScene & entity)
{
	// �r���A�[��Active On

	// �K�C�h���̉�ʂ��\��
	GuideViewer::Instance()->SetActive(false);

	Tween::SetPause(true);
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameInterrupt::OnUpdate(GameScene & entity)
{
	if (Keyboard::GetTrigger(DIK_V))
	{
		entity.ChangeState(entity.prevState);

		// �r���A�[��Active Off

		// Tween�N���X�̃|�[�Y�t���O��ݒu����
		Tween::SetPause(false);
	}
	else if (Keyboard::GetTrigger(DIK_2))
	{
		PlayBGM::Instance()->FadeOut();

		TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
		{
			// Tween�N���X�̃|�[�Y�t���O��ݒu����
			Tween::SetPause(false);

			entity.level = 0;
			entity.Clear();
			entity.SetFieldLevel(0);
			entity.field->Load();
			entity.ChangeState(State::Title);
		});
	}

	return State::Interrupt;
}
