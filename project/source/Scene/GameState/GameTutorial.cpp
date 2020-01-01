//=============================================================================
//
// �`���[�g���A���N���X [GameTutorial.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "GameTutorial.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../../Framework/Input/input.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../Viewer/TitleScene/TitleViewer.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"


/**************************************
���ꏈ��
***************************************/
void GameScene::GameTutorial::OnStart(GameScene & entity)
{
	// �J�����̏œ_���Z�b�g
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

	// �Q�[���V�[���Ŏg�p����UI�̕`���ON
	entity.field->SetViewerActive(true);
	entity.gameViewer->SetActive(true);
	GuideViewer::Instance()->SetActive(true);

	entity.remainTime = 30 * 999;
}


/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameTutorial::OnUpdate(GameScene & entity)
{
	//���͊m�F
	entity.field->CheckInput();

	//�t�B�[���h�X�V
	entity.field->UpdateLogic();
	entity.field->UpdateObject();

	//���i���[�h�ւ̑J�ڊm�F
	if (entity.field->ShouldSwicthCamera())
	{
		entity.ChangeState(State::FarView);
	}
	//�J��������]�����邩
	else if (entity.field->ShouldRotateCamera())
	{
		entity.fieldCamera->ChangeMode(FieldCamera::AngleRotate);
	}

	if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		entity.level = 0;
		entity.InTutorial = false;
		entity.remainTime = 30 * 180;

		entity.ChangeState(GameScene::State::TransitionOut);
	}

	return State::Tutorial;
}
