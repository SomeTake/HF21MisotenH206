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

//�����̃z�b�v��
static const float hopNumValue = 30.0f;

//�����̏����T�C�Y
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(42.0f, 42.0f, 0.0f);

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ItemStockViewer::ItemStockViewer()
{
	//����
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
	num->MakeVertex();
	num->size = initNumSize;
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.21f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	num->SetColor(SET_COLOR_NOT_COLORED);
	num->intervalNumberScr = 42.0f;
	num->intervalNumberTex = 0.10f;
	num->placeMax = 2;
	num->baseNumber = 10;
	num->isHopped = false;
	num->radian = 0;

	//�A�C�R��
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Drill.png");
	icon->MakeVertex();
	icon->size = D3DXVECTOR3(180.0f, 135.0f, 0.0f);
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.7f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->SetColor(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ItemStockViewer::~ItemStockViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(icon);
}

//=============================================================================
// �X�V����
//=============================================================================
void ItemStockViewer::Update(void)
{
	//�A�j���[�V����
	Hop();
}

//=============================================================================
// �`�揈��
//=============================================================================
void ItemStockViewer::Draw(void)
{
	//�A�C�R��
	icon->Draw();
	icon->SetVertex();

	//����
	num->DrawCounter(num->baseNumber, parameterBox, num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);
}

//=============================================================================
// �A�j���[�V��������
//=============================================================================
void ItemStockViewer::Hop(void)
{
	//�O�t���[���̃p�����[�^�Ƃ̍���0�łȂ��Ƃ��z�b�s���O��Ԃɂ���
	currentParam = parameterBox;
	if (currentParam - lastParam != 0)
	{
		num->isHopped = true;
	}
	lastParam = parameterBox;

	//�z�b�s���O����
	num->size.y = num->HopNumber(num->size.y, initNumSize.y, hopNumValue);
}
