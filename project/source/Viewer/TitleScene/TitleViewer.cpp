//=====================================
//
// �^�C�g���r���A�[[TitleViewer.cpp]
// �@�\�F�^�C�g�����UI�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "TitleViewer.h"
#include "TitleLogo.h"
#include "SelectViewer.h"
#include "RewardViewer.h"
#include "../../../Framework/Input/input.h"
#include "../../Scene/GameScene.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"

//=====================================
// �R���X�g���N�^
//=====================================
TitleViewer::TitleViewer()
{
	logo = new TitleLogo();
	selectViewer = new SelectViewer();
	rewardViewer = new RewardViewer();
}

//=====================================
// �f�X�g���N�^
//=====================================
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(logo);
	SAFE_DELETE(selectViewer);
	SAFE_DELETE(rewardViewer);
}

//=====================================
// �X�V
//=====================================
void TitleViewer::Update()
{
	logo->Update();
	if (!rewardViewer->isPlaying)
	{
		selectViewer->Update();
	}
	else
	{
		rewardViewer->Update();
	}
}

//=====================================
// �`��
//=====================================
void TitleViewer::Draw()
{
	if (!isActive)
		return;

	if (!rewardViewer->isPlaying)
	{
		logo->Draw();

		// �ʃE�C���h�E���쐬����̂ōŌ�
		selectViewer->Draw();
	}
	else
	{
		rewardViewer->Draw();
	}
}

//=====================================
// �`��ۃt���O�̃Z�b�g
//=====================================
void TitleViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=====================================
// �V�[���`�F���W
//=====================================
bool TitleViewer::CheckSceneChange()
{
	if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		SE::Play(SoundConfig::SEID::Select01, 1.0f);
		return true;
	}
	else
	{
		return false;
	}
}

//=====================================
// ���̃V�[�����w�肷��
//=====================================
void TitleViewer::SetNextScene(GameScene& entity)
{
	// �����[�h�r���[�A���\�����Ă��Ȃ����
	if (!rewardViewer->isPlaying)
	{
		if (selectViewer->CheckNextScene() == 0)
		{
			// �Q�[���J�n
			PlayBGM::Instance()->FadeOut();
			PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::City, 0.1f, 30);
			entity.ChangeState(GameScene::State::Idle);
		}
		else if (selectViewer->CheckNextScene() == 1)
		{
			// �g���t�B�[�m�F
			rewardViewer->isPlaying = true;
		}
		else if (selectViewer->CheckNextScene() == 2)
		{
			// �Q�[���I��
			PostQuitMessage(0);
		}
	}
}

//=====================================
// �Z���N�g���S�̕\����"�Q�[���J�n"�ɐݒ肷��
//=====================================
void TitleViewer::InitSelectLogo(void)
{
	//selectViewer->InitSelectLogo();
}
