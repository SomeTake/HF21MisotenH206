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
#include "../../../Framework/Task/TaskManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
TitleViewer::TitleViewer() :
	cntFrame(0), isSelect(false), isFlash(false)
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
	if (!isActive)
		return;

	logo->Update();
	if (!rewardViewer->isPlaying)
	{
		if (isSelect)
		{
			// �_�ŏ���
			cntFrame++;
			if (isFlash)
			{
				if (cntFrame % 5 == 0)
				{
					isFlash = false;
				}
			}
			else
			{
				if (cntFrame % 5 == 0)
				{
					isFlash = true;
				}
			}
			//return;
		}
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

		if (isFlash)
			return;

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
	if (isSelect)
		return false;

	if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		SE::Play(SoundConfig::SEID::Select01, 1.0f);
		isSelect = true;
		isFlash = true;
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
		if (!isSelect)
			return;

		if (selectViewer->CheckNextScene() == 0)
		{
			// �Q�[���J�n
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::City, 0.1f, 30);
				entity.ChangeState(GameScene::State::Idle);
				//isActive = true;
				isSelect = false;
				isFlash = false;
				cntFrame = 0;
			});
			PlayBGM::Instance()->FadeOut();
		}
		else if (selectViewer->CheckNextScene() == 1)
		{
			// �Q�[���J�n
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				// �g���t�B�[�m�F
				rewardViewer->isPlaying = true;
				isActive = true;
				isFlash = false;
				isSelect = false;
				cntFrame = 0;
			});
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
