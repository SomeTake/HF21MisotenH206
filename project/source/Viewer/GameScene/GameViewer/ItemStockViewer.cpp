//=============================================================================
//
// �X�g�b�N�r���A�[���� [ItemStockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "../../../../Framework/Math/Easing.h"
#include "ItemStockViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
// �X�g�b�N�g�p�֎~���ʂ̌p���t���[��
// �{����300�t���[���̂͂������A�o�ꉉ�o��30�t���[�������炳�Ȃ��Ɖ��o�����ꂶ�Ⴄ
static const int DefaultDebuffCount = 270;

//�����̃z�b�v��
static const float hopNumValue = 30.0f;

//�����̏����T�C�Y
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(42.0f, 42.0f, 0.0f);

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ItemStockViewer::ItemStockViewer() :
	InBanStock(false)
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

	//�X�g�b�N�A�C�R��
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Drill.png");
	icon->MakeVertex();
	icon->size = D3DXVECTOR3(180.0f, 135.0f, 0.0f);
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.7f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->SetColor(SET_COLOR_NOT_COLORED);

	//�o�c�A�C�R��
	BanIcon = new BaseViewerDrawer();
	BanIcon->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/BanStock.png");
	BanIcon->size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	BanIcon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BanIcon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.5f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	BanIcon->SetColor(SET_COLOR_NOT_COLORED);
	BanIcon->MakeVertex();

	//�o�c�A�C�R��
	BanIcon_White = new BaseViewerDrawer();
	BanIcon_White->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/BanStock_White.png");
	BanIcon_White->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	BanIcon_White->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BanIcon_White->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.5f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	BanIcon_White->SetColor(SET_COLOR_NOT_COLORED);
	BanIcon_White->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ItemStockViewer::~ItemStockViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(icon);
	SAFE_DELETE(BanIcon);
	SAFE_DELETE(BanIcon_White);
}

//=============================================================================
// �X�V����
//=============================================================================
void ItemStockViewer::Update(void)
{
	//�A�j���[�V����
	Animate();
}

//=============================================================================
// �`�揈��
//=============================================================================
void ItemStockViewer::Draw(void)
{
	//�A�C�R��
	icon->SetVertex();
	icon->Draw();

	//����
	num->DrawCounter(num->baseNumber, parameterBox, num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);

	// �o�c�A�C�R��
	if (InBanStock)
	{
		BanIcon_White->Draw();
		BanIcon->Draw();
	}
}

//=============================================================================
// �A�j���[�V��������
//=============================================================================
void ItemStockViewer::Animate(void)
{
	//���݂̃p�����[�^
	static int currentParam;

	//�P�t���[���O�̃p�����[�^
	static int lastParam;

	static int FrameCount = 0;

	//�O�t���[���̃p�����[�^�Ƃ̍���0�łȂ��Ƃ��z�b�s���O��Ԃɂ���
	currentParam = parameterBox;
	if (currentParam - lastParam != 0)
	{
		num->isHopped = true;
	}
	lastParam = parameterBox;

	//�z�b�s���O����
	num->size.y = num->HopNumber(num->size.y, initNumSize.y, hopNumValue);

	if (InBanStock)
	{
		if (BanIconDebut)
		{
			// �o�c�A�C�R���o��̉��o
			FrameCount++;

			float Size = Easing::EaseValue((float)FrameCount / 30, 200.0f, 100.0f, InExpo);

			if (Size <= 100.0f)
			{
				FrameCount = DefaultDebuffCount;
				BanIconDebut = false;
			}

			BanIcon->size = D3DXVECTOR3(Size, Size, 0.0f);
			BanIcon_White->size = D3DXVECTOR3(Size, Size, 0.0f);
			// BaseViewerDrawer�̒��_�ݒu�֐�
			BanIcon->SetVertex();
			BanIcon_White->SetVertex();
		}
		else
		{
			float RemainTimePercent = (float)FrameCount / (float)DefaultDebuffCount;
			float Percent = Easing::EaseValue((1 - RemainTimePercent), 1.0f, -1.0f, EaseType::Linear);

			FrameCount--;
			// ItemStockViewer�̒��_�ݒu�֐��A���ʂ��Ⴄ
			SetBanIconVertex(Percent);
			SetBanIconTexture(RemainTimePercent);
		}
	}
}

//=============================================================================
// �o�c�A�C�R���̒��_���ݒ�
//=============================================================================
void ItemStockViewer::SetBanIconVertex(float Percent)
{
	BanIcon->vertexWk[0].vtx = BanIcon->position + D3DXVECTOR3(-BanIcon->size.x, -BanIcon->size.y * Percent, 0.0f);
	BanIcon->vertexWk[1].vtx = BanIcon->position + D3DXVECTOR3(BanIcon->size.x, -BanIcon->size.y * Percent, 0.0f);
	BanIcon->vertexWk[2].vtx = BanIcon->position + D3DXVECTOR3(-BanIcon->size.x, BanIcon->size.y, 0.0f);
	BanIcon->vertexWk[3].vtx = BanIcon->position + D3DXVECTOR3(BanIcon->size.x, BanIcon->size.y, 0.0f);

	BanIcon_White->vertexWk[0].vtx = BanIcon_White->position + D3DXVECTOR3(-BanIcon_White->size.x, -BanIcon_White->size.y, 0.0f);
	BanIcon_White->vertexWk[1].vtx = BanIcon_White->position + D3DXVECTOR3(BanIcon_White->size.x, -BanIcon_White->size.y, 0.0f);
	BanIcon_White->vertexWk[2].vtx = BanIcon_White->position + D3DXVECTOR3(-BanIcon_White->size.x, BanIcon_White->size.y * -Percent, 0.0f);
	BanIcon_White->vertexWk[3].vtx = BanIcon_White->position + D3DXVECTOR3(BanIcon_White->size.x, BanIcon_White->size.y * -Percent, 0.0f);
}

//=============================================================================
// �o�c�A�C�R���̃e�N�X�`�����ݒ�
//=============================================================================
void ItemStockViewer::SetBanIconTexture(float Percent)
{
	BanIcon->vertexWk[0].tex = D3DXVECTOR2(0.0f, (1 - Percent));
	BanIcon->vertexWk[1].tex = D3DXVECTOR2(1.0f, (1 - Percent));
	BanIcon->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	BanIcon->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	BanIcon_White->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	BanIcon_White->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	BanIcon_White->vertexWk[2].tex = D3DXVECTOR2(0.0f, (1 - Percent));
	BanIcon_White->vertexWk[3].tex = D3DXVECTOR2(1.0f, (1 - Percent));
}