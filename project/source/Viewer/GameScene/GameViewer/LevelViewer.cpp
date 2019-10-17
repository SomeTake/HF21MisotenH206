//=============================================================================
//
// AI���x���r���A�[���� [LevelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/CircleGauge.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "LevelViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
LevelViewer::LevelViewer()
{
	//����
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Num.png");
	num->MakeVertex();
	num->size = D3DXVECTOR3(20.0f, 46.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.550f, SCREEN_HEIGHT / 10 * 1.50f, 0.0f);
	num->SetColor(SET_COLOR_NOT_COLORED);
	ratioLevelBox = 1.0;
	levelAI_Box = 0;
	num->intervalNumberScr = 40.0f;
	num->intervalNumberTex = 0.1f;
	num->placeMax = 5;
	num->baseNumber = 10;

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/BG.png");
	bg->MakeVertex();
	bg->size = D3DXVECTOR3(128.0f, 128.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.0f, SCREEN_HEIGHT / 10 * 1.50f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);

	//�~�Q�[�W
	circleGuage = new CircleGauge(D3DXVECTOR2(128.0f, 128.0f));
	circleGuage->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
	circleGuage->SetScale(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	circleGuage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	circleGuage->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.0f, SCREEN_HEIGHT / 10 * 1.50f, 0.0f));
	circleGuage->SetFillStart(circleGuage->Top);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
LevelViewer::~LevelViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(bg);
	SAFE_DELETE(circleGuage);
}

//=============================================================================
// �X�V����
//=============================================================================
void LevelViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void LevelViewer::Draw(void)
{
	//�w�i���ɕ`��
	bg->SetVertex();
	bg->Draw();

	circleGuage->SetPercent(ratioLevelBox);
	circleGuage->Draw();

	num->DrawCounter(num->baseNumber, levelAI_Box, num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);
}
