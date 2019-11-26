//=============================================================================
//
// ���ʃX�R�A�r���A�[���� [ResultScoreViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "ResultScoreViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ResultScoreViewer::ResultScoreViewer() :parameterBox()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 tex;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/Number.png",
		&tex);

	for (int i = 0; i < fieldTypeMax; i++)
	{
		num[i] = new CountViewerDrawer();
		num[i]->texture = tex;
		num[i]->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
		num[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		num[i]->intervalPosScr = 80.0f;
		num[i]->intervalPosTex = 0.1f;
		num[i]->baseNumber = 10;
	}

	SetViewerPos();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ResultScoreViewer::~ResultScoreViewer()
{
	for (int i = 0; i < fieldTypeMax; i++)
	{
		SAFE_DELETE(num[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void ResultScoreViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void ResultScoreViewer::Draw(void)
{
	for (int i = 0; i < fieldTypeMax; i++)
	{
		num[i]->DrawCounter(num[i]->baseNumber,
			parameterBox[i], num[i]->placeMax,
			num[i]->intervalPosScr, num[i]->intervalPosTex);
	}
}

//=============================================================================
// �r���A�[���W�ݒ菈���i���t�@�N�^�����O�\��j
//=============================================================================
void ResultScoreViewer::SetViewerPos(void)
{
	num[0]->placeMax = 4;
	num[1]->placeMax = 4;
	num[2]->placeMax = 8;

	for (int i = 0; i < fieldTypeMax; i++)
	{
		int placeCnt[fieldTypeMax] = {
			num[0]->placeMax,
			num[0]->placeMax + num[1]->placeMax,
			num[0]->placeMax + num[1]->placeMax + num[2]->placeMax };

		float pos = placeCnt[i] * num[i]->intervalPosScr;

		num[i]->position = D3DXVECTOR3(
			SCREEN_WIDTH/2 
			+ num[i]->intervalPosScr/2 
			+ (num[0]->placeMax + num[1]->placeMax + num[2]->placeMax)/2*num[i]->intervalPosScr 
			- pos, SCREEN_CENTER_Y, 0.0f);
		num[i]->MakeVertex();
	}
}