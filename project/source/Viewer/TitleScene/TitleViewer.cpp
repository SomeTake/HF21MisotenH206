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
	if (!isActive)
		return;

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
// ���̃V�[�����w�肷��
//=====================================
TitleViewer::MenuID TitleViewer::GetSelectedMenu()
{
	// �����[�h�r���[�A���\�����Ă��Ȃ����
	if (rewardViewer->isPlaying)
		return None;

	int next = selectViewer->CheckNextScene();

	if (next == 0)
		return StartGame;
	
	if (next == 1)
		return ViewReward;

	if (next == 2)
		return QuitGame;

	return None;
}

//=====================================
// ���уr���[�A�̃Z�b�g
//=====================================
void TitleViewer::SetRewardViewer()
{
	rewardViewer->isPlaying = true;
}

//=====================================
// �Z���N�g���S�̕\����"�Q�[���J�n"�ɐݒ肷��
//=====================================
void TitleViewer::InitSelectLogo(void)
{
	//selectViewer->InitSelectLogo();
}
