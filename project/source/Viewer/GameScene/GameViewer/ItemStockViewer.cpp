//=============================================================================
//
// �X�g�b�N�r���A�[���� [ItemStockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "ItemStockViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�X�g�b�N�r���A�[�̎�ސ�
const int ItemStockViewer::typeMax;

//�r���A�[�̕\���Ԋu
static const float intervalViewerPos = 220.0f;

//�A�C�e���A�C�R���e�N�X�`���p�X
static const char *iconTexPath[ItemStockViewer::typeMax]
{
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Bridge.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Drill.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/Insurance.png",
	"data/TEXTURE/Viewer/GameViewer/StockViewer/EDF.png",
};

//�����̃z�b�v��
static const float hopNumValue = 30.0f;

//�����̏����T�C�Y
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(42.0f, 42.0f, 0.0f);

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ItemStockViewer::ItemStockViewer()
{
	for (int  i = 0; i < typeMax; i++)
	{
		//����
		num[i] = new CountViewerDrawer();
		num[i]->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
		num[i]->MakeVertex();
		num[i]->size = initNumSize;
		num[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		num[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.21f, SCREEN_HEIGHT / 10 * 2.70f + i*intervalViewerPos, 0.0f);
		num[i]->SetColor(SET_COLOR_NOT_COLORED);
		num[i]->intervalNumberScr = 42.0f;
		num[i]->intervalNumberTex = 0.10f;
		num[i]->placeMax = 2;
		num[i]->baseNumber = 10;
		num[i]->isHopped = false;
		num[i]->radian = 0;

		//�A�C�R��
		icon[i] = new BaseViewerDrawer();
		icon[i]->LoadTexture(iconTexPath[i]);
		icon[i]->MakeVertex();
		icon[i]->size = D3DXVECTOR3(180.0f, 135.0f, 0.0f);
		icon[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		icon[i]->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.7f, SCREEN_HEIGHT / 10 * 2.70f + i * intervalViewerPos, 0.0f);
		icon[i]->SetColor(SET_COLOR_NOT_COLORED);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ItemStockViewer::~ItemStockViewer()
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
void ItemStockViewer::Update(void)
{
	Animate();
}

//=============================================================================
// �`�揈��
//=============================================================================
void ItemStockViewer::Draw(void)
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
void ItemStockViewer::Animate(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		//�O�t���[���̃p�����[�^�Ƃ̍���0�o�Ȃ��Ƃ��z�b�s���O��Ԃɂ���
		currentParam[i] = parameterBox[i];
		if (currentParam[i] - lastParam[i] != 0)
		{
			num[i]->isHopped = true;
		}
		lastParam[i] = parameterBox[i];

		//�z�b�s���O����
		num[i]->size.y = num[i]->HopNumber(num[i]->size.y, initNumSize.y, hopNumValue);
	}
}
