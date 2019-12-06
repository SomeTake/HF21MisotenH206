//=============================================================================
//
// �^�C�}�[�r���A�[���� [TimerViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "TimerViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
TimerViewer::TimerViewer()
{
	isPlaying = true;

	//������
	intNum = new CountViewerDrawer();
	intNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	intNum->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	intNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	intNum->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.3f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	intNum->intervalPosScr = 80.0f;
	intNum->intervalPosTex = 0.1f;
	intNum->placeMax = 3;
	intNum->baseNumber = 10;
	intNum->MakeVertex();

	//������
	fewNum = new CountViewerDrawer();
	fewNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	fewNum->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	fewNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fewNum->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.70f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	fewNum->intervalPosScr = 80.0f;
	fewNum->intervalPosTex = 0.1f;
	fewNum->placeMax = 2;
	fewNum->baseNumber = 10;
	fewNum->MakeVertex();

	//�����_
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Point.png");
	point->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(intNum->position.x + intNum->intervalPosScr*2.80f, SCREEN_HEIGHT / 10 * 1.0f,0.0f);
	point->MakeVertex();

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/BG.png");
	bg->size = D3DXVECTOR3(460.0f, 200.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 1.250), SCREEN_HEIGHT / 10 * 0.920f, 0.0f);
	bg->MakeVertex();
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
	if (!isPlaying)
		return;

	//�w�i���ɕ`��
	bg->Draw();

	//�����_
	point->Draw();

	//������
	intNum->DrawCounter(intNum->baseNumber,
		(int)parameterBox, intNum->placeMax,
		intNum->intervalPosScr, intNum->intervalPosTex);

	//������
	fewNum->DrawCounter(fewNum->baseNumber, 
		(int)((parameterBox - (int)parameterBox)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
		fewNum->intervalPosScr, fewNum->intervalPosTex);
}