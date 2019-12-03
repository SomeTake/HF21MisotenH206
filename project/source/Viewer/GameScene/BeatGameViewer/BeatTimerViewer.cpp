//=============================================================================
//
// �^�C�}�[�r���A�[���� [BeatTimerViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "BeatTimerViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BeatTimerViewer::BeatTimerViewer()
{
	//������
	intNum = new CountViewerDrawer();
	intNum->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Number.png");
	intNum->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	intNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	intNum->position = D3DXVECTOR3(SCREEN_WIDTH/10*4.80f, SCREEN_HEIGHT/4, 0.0f);
	intNum->intervalPosScr = 80.0f;
	intNum->intervalPosTex = 0.1f;
	intNum->placeMax = 1;
	intNum->baseNumber = 10;
	intNum->MakeVertex();

	//�����_
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Point.png");
	point->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(intNum->position.x + intNum->intervalPosScr/2, SCREEN_HEIGHT/4, 0.0f);
	point->MakeVertex();

	//������
	fewNum = new CountViewerDrawer();
	fewNum->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Number.png");
	fewNum->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	fewNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fewNum->position = D3DXVECTOR3(point->position.x + intNum->intervalPosScr/2, SCREEN_HEIGHT/4, 0.0f);
	fewNum->intervalPosScr = 70.0f;
	fewNum->intervalPosTex = 0.1f;
	fewNum->placeMax = 2;
	fewNum->baseNumber = 10;
	fewNum->MakeVertex();
	
	//�O�̃e�L�X�g
	frontText = new BaseViewerDrawer();
	frontText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Text.png");
	frontText->size = D3DXVECTOR3(200.0f, 150.0f, 0.0f);
	frontText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frontText->position = D3DXVECTOR3(intNum->position.x - intNum->intervalPosScr*1.50f, SCREEN_HEIGHT/4 - 5.0f, 0.0f);
	frontText->MakeVertex();
	frontText->SetTexture(1, 2, 0);

	//���̃e�L�X�g
	backText = new BaseViewerDrawer();
	backText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTimerViewer/Text.png");
	backText->size = D3DXVECTOR3(200.0f, 150.0f, 0.0f);
	backText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	backText->position = D3DXVECTOR3(fewNum->position.x + intNum->intervalPosScr*fewNum->placeMax, SCREEN_HEIGHT/4 - 5.0f, 0.0f);
	backText->MakeVertex();
	backText->SetTexture(1, 2, 1);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BeatTimerViewer::~BeatTimerViewer()
{
	SAFE_DELETE(intNum);
	SAFE_DELETE(fewNum);
	SAFE_DELETE(point);
	SAFE_DELETE(frontText);
	SAFE_DELETE(backText);
}

//=============================================================================
// �X�V����
//=============================================================================
void BeatTimerViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void BeatTimerViewer::Draw(void)
{
	//�w�i���ɕ`��
	frontText->Draw();

	//�w�i���ɕ`��
	backText->Draw();

	//�����_
	point->Draw();

	//������
	intNum->DrawCounter(intNum->baseNumber,
		(int)time, intNum->placeMax,
		intNum->intervalPosScr, intNum->intervalPosTex);

	//������
	fewNum->DrawCounter(fewNum->baseNumber,
		(int)((time - (int)time)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
		fewNum->intervalPosScr, fewNum->intervalPosTex);
}

//=============================================================================
// �Z�b�g����
//=============================================================================
void BeatTimerViewer::Set(float time)
{
	//�^�C�}�[���Z�b�g
	this->time = time;
}
