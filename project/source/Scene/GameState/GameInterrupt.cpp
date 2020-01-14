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
#include "../../Viewer/GameScene/SuspendViewer/SuspendViewer.h"
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
	entity.suspendViewer->SetActive(true);

	// �K�C�h���̉�ʂ��\��
	GuideViewer::Instance()->SetActive(false);

	// Tween�N���X�̃|�[�Y�t���O��ݒu����
	Tween::SetPause(true);
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameInterrupt::OnUpdate(GameScene & entity)
{
	entity.suspendViewer->Update();

	if (Keyboard::GetTrigger(DIK_Z) || Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		// ������
		if (entity.suspendViewer->GetSelected() == SuspendViewer::Dialog::No)
		{
			// �K�C�h���̉�ʂ�\��
			GuideViewer::Instance()->SetActive(true);

			// �r���A�[��Active Off
			entity.suspendViewer->SetActive(false);

			// Tween�N���X�̃|�[�Y�t���O��ݒu����
			Tween::SetPause(false);

			entity.ChangeState(entity.prevState);
		}
		// �͂�
		else if (entity.suspendViewer->GetSelected() == SuspendViewer::Dialog::Yes)
		{
			PlayBGM::Instance()->FadeOut();

			// �r���A�[��Active Off
			entity.suspendViewer->SetActive(false);

			TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
			{
				// Tween�N���X�̃|�[�Y�t���O��ݒu����
				Tween::SetPause(false);

				entity.level = 0;
				entity.Clear();
				entity.SetFieldLevel(0);
				entity.field->Load(entity.csvNo);
				entity.ChangeState(State::Title);
			});
		}
	}

	return State::Interrupt;
}
