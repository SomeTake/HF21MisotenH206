//=============================================================================
//
// ���ʃ����L���O�r���A�[���� [ResultRankingViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "ResultRankingViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ResultRankingViewer::ResultRankingViewer()
{
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultRankingViewer/Number.png");
	num->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.3f, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	num->intervalPosScr = 80.0f;
	num->intervalPosTex = 0.1f;
	num->placeMax = 3;
	num->baseNumber = 10;
	num->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ResultRankingViewer::~ResultRankingViewer()
{
	SAFE_DELETE(num);
}

//=============================================================================
// �X�V����
//=============================================================================
void ResultRankingViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void ResultRankingViewer::Draw(void)
{
	num->DrawCounter(num->baseNumber,
		(int)parameterBox, num->placeMax,
		num->intervalPosScr, num->intervalPosTex);
}