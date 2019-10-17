//=============================================================================
//
// �X�g�b�N�r���A�[���� [StockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "StockViewer.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�X�g�b�N�r���A�[�̎�ސ�
const int StockViewer::typeMax;

//�r���A�[�̕\���Ԋu
static const float intervalViewerPos = 220.0f;

//�A�C�e���A�C�R���e�N�X�`���p�X
static const char *iconTexPath[StockViewer::typeMax]
{
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Bridge.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Drill.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Insurance.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/EDF.png",
};

//�����̃z�b�v��
static const float hopNumValue = 30.0f;

//�����̏����T�C�Y
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(20.0f, 46.0f, 0.0f);

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
StockViewer::StockViewer()
{
	for (int  i = 0; i < typeMax; i++)
	{
		//����
		num[i] = new CountViewerDrawer();
		num[i]->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
		num[i]->MakeVertex();
		num[i]->size = initNumSize;
		num[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		num[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.3f, SCREEN_HEIGHT / 10 * 2.50f + i*intervalViewerPos, 0.0f);
		num[i]->SetColor(SET_COLOR_NOT_COLORED);
		parameterBox[i] = 0;
		num[i]->intervalNumberScr = 120.0f;
		num[i]->intervalNumberTex = 0.10f;
		num[i]->placeMax = 1;
		num[i]->baseNumber = 10;
		num[i]->isHopped = false;
		num[i]->radian = 0;

		//�A�C�R��
		icon[i] = new BaseViewerDrawer();
		icon[i]->LoadTexture(iconTexPath[i]);
		icon[i]->MakeVertex();
		icon[i]->size = D3DXVECTOR3(180.0f, 135.0f, 0.0f);
		icon[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		icon[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.7f, SCREEN_HEIGHT / 10 * 2.50f + i * intervalViewerPos, 0.0f);
		icon[i]->SetColor(SET_COLOR_NOT_COLORED);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
StockViewer::~StockViewer()
{
	for (int i = 0; i < typeMax; i++)
	{
		SAFE_DELETE(num[i]);
		SAFE_DELETE(icon[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void StockViewer::Update(void)
{
	Animate();
}

//=============================================================================
// �`�揈��
//=============================================================================
void StockViewer::Draw(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		icon[i]->Draw();
		icon[i]->SetVertex();

		num[i]->DrawCounter(num[i]->baseNumber, parameterBox[i], num[i]->placeMax,
			num[i]->intervalNumberScr, num[i]->intervalNumberTex);
	}
}

//=============================================================================
// �A�j���[�V��������
//=============================================================================
void StockViewer::Animate(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		//�z�b�s���O����
		num[i]->size.y = num[i]->HopNumber(num[i]->size.y, initNumSize.y, hopNumValue);
	}
}
