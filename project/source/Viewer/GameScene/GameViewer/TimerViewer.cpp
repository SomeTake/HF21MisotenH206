//=============================================================================
//
// �^�C�}�[�r���A�[���� [TimerViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "TimerViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
TimerViewer::TimerViewer()
{
	//����
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	num->MakeVertex();
	num->size = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.5f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	num->SetColor(SET_COLOR_YELLOW);
	num->parameterBox = 0;
	num->intervalNumberScr = 60.0f;
	num->intervalNumberTex = 0.1f;
	num->placeMax = 3;
	num->baseNumber = 10;

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/BG.png");
	bg->MakeVertex();
	bg->size = D3DXVECTOR3(204.80f, 51.20f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.3, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
TimerViewer::~TimerViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(bg);
}

//=============================================================================
// �X�V����
//=============================================================================
void TimerViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void TimerViewer::Draw(void)
{
	//�w�i���ɕ`��
	bg->Draw();
	bg->SetVertex();

	num->DrawCounter(num->baseNumber, num->parameterBox, num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);
}