//=============================================================================
//
// �O���[�h�A�b�v�N���X [GradeUpViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../../main.h"
#include "GradeUpViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Task/TaskManager.h"

const D3DXVECTOR3 AILevelDefaultPos = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, 130.0f, 0.0f);
const D3DXVECTOR3 TextDefaultPos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT + 384.0f, 0.0f);
const float ScaleNum = 1.5f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
GradeUpViewer::GradeUpViewer(void) :
	Callback(nullptr)
{
	isPlaying = true;

	GradeUpText = new TextureDrawer(D3DXVECTOR2(1024.0f, 384.0f));
	GradeUpText->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/GradeUp.png");
	GradeUpText->SetPosition(TextDefaultPos);
	GradeUpText->SetAlpha(0.0f);

	AILevelTex = new TextureDrawer(D3DXVECTOR2(250.0f, 250.0f), false);
	AILevelTex->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/AILevel.png");
	AILevelTex->SetPosition(AILevelDefaultPos);
	AILevelTex->SetScale(ScaleNum);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
GradeUpViewer::~GradeUpViewer()
{
	SAFE_DELETE(GradeUpText);
	SAFE_DELETE(AILevelTex);
}

//=============================================================================
// �X�V
//=============================================================================
void GradeUpViewer::Update()
{
	if (!isPlaying)
		return;

	GradeUpText->Update();
	AILevelTex->Update();
}

//=============================================================================
// �`��
//=============================================================================
void GradeUpViewer::Draw()
{
	if (!isPlaying)
		return;

	AILevelTex->Draw();
	GradeUpText->Draw();
}

//=============================================================================
// �O���[�h�A�b�v���o��ݒu
//=============================================================================
void GradeUpViewer::SetGradeUp(std::function<void(void)> callback)
{
	Callback = callback;
	isPlaying = true;

	// ������
	AILevelTex->SetVisible(true);
	AILevelTex->SetScale(1 / ScaleNum);
	AILevelTex->SetAlpha(1.0f);
	AILevelTex->SetPosition(AILevelDefaultPos);

	// ��ʒ����Ɉړ����Ȃ���g��
	AILevelTex->Move(60.0f, D3DXVECTOR3(SCREEN_CENTER_X, 284.0f, 0.0f), EaseType::OutCubic);
	AILevelTex->SetScale(60.0f, ScaleNum, EaseType::OutCubic, [&]()
	{
		TextPopUp();
	});

	TaskManager::Instance()->CreateDelayedTask(180, [&]()
	{
		GradeUpFadeOut();
	});
}

//=============================================================================
// �e�L�X�g�̃|�b�v�A�b�v���o��ݒu
//=============================================================================
void GradeUpViewer::TextPopUp(void)
{
	// ������
	GradeUpText->SetAlpha(0.0f);
	GradeUpText->SetPosition(TextDefaultPos);

	// ��ʒ����Ɉړ����Ȃ���t�F�C�h�C��
	GradeUpText->Fade(60.0f, 1.0f);
	GradeUpText->Move(60.0f, D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), EaseType::OutCubic);
}

//=============================================================================
// �t�F�C�h�A�E�g���o��ݒu
//=============================================================================
void GradeUpViewer::GradeUpFadeOut()
{
	// ��ʏ���Ɉړ����Ȃ���t�F�C�h�A�E�g
	GradeUpText->Move(60.0f, D3DXVECTOR3(SCREEN_CENTER_X, -384.0f, 0.0f), EaseType::OutCubic);
	GradeUpText->Fade(60.0f, 0.0f);

	// �t�F�C�h�A�E�g
	AILevelTex->Fade(60.0f, 0.0f, [&]()
	{
		isPlaying = false;
		if (Callback != nullptr)
			Callback();
	});
}

