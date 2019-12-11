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
#include "../../../Framework/Input/input.h"
#include "../../Scene/GameScene.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

//=====================================
// �R���X�g���N�^
//=====================================
TitleViewer::TitleViewer()
{
	logo = new TitleLogo();
	selectViewer = new SelectViewer();
}

//=====================================
// �f�X�g���N�^
//=====================================
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(logo);
	SAFE_DELETE(selectViewer);
}

//=====================================
// �X�V
//=====================================
void TitleViewer::Update()
{
	logo->Update();
	selectViewer->Update();
}

//=====================================
// �`��
//=====================================
void TitleViewer::Draw()
{
	if (!isActive)
		return;

	logo->Draw();

	// �ʃE�C���h�E���쐬����̂ōŌ�
	selectViewer->Draw();
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
	return Keyboard::GetTrigger(DIK_RETURN);
}

//=====================================
// ���̃V�[�����w�肷��
//=====================================
void TitleViewer::SetNextScene(GameScene& entity)
{
	if (selectViewer->CheckNextScene() == 0)
	{
		PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::Title, 0.1f, 30, true);
		PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::City, 0.1f, 30);
		entity.ChangeState(GameScene::State::Idle);
	}
	else if (selectViewer->CheckNextScene() == 1)
	{
		// �g���t�B�[�m�F
	}
	else if (selectViewer->CheckNextScene() == 2)
	{
		// �Q�[���I��
		PostQuitMessage(0);
	}
}
