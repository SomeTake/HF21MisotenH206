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
	//������
	intNum = new CountViewerDrawer();
	intNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	intNum->MakeVertex();
	intNum->size = D3DXVECTOR3(60.0f, 60.0f, 0.0f);
	intNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//intNum->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.3f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	intNum->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.3f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	intNum->SetColor(SET_COLOR_NOT_COLORED);
	intNum->intervalNumberScr = 80.0f;
	intNum->intervalNumberTex = 0.1f;
	intNum->placeMax = 3;
	intNum->baseNumber = 10;

	//������
	fewNum = new CountViewerDrawer();
	fewNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	fewNum->MakeVertex();
	fewNum->size = D3DXVECTOR3(60.0f, 60.0f, 0.0f);
	fewNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fewNum->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.7f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	fewNum->SetColor(SET_COLOR_NOT_COLORED);
	fewNum->intervalNumberScr = 80.0f;
	fewNum->intervalNumberTex = 0.1f;
	fewNum->placeMax = 2;
	fewNum->baseNumber = 10;

	//�����_
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Point.png");
	point->MakeVertex();
	point->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(intNum->position.x + intNum->intervalNumberScr*2.8f, SCREEN_HEIGHT / 10 * 0.90f,0.0f);
	point->SetColor(SET_COLOR_NOT_COLORED);

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/BG.png");
	bg->MakeVertex();
	bg->size = D3DXVECTOR3(230.0f, 100.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 1.25), SCREEN_HEIGHT / 10 * 0.920f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
TimerViewer::~TimerViewer()
{
	SAFE_DELETE(intNum);
	SAFE_DELETE(fewNum);
	SAFE_DELETE(point);
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

	//�����_
	point->Draw();
	point->SetVertex();

	//������
	intNum->DrawCounter(intNum->baseNumber, (int)parameterBox, intNum->placeMax,
		intNum->intervalNumberScr, intNum->intervalNumberTex);

	//������
	fewNum->DrawCounter(fewNum->baseNumber, (int)((parameterBox - (int)parameterBox)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
		fewNum->intervalNumberScr, fewNum->intervalNumberTex);
}