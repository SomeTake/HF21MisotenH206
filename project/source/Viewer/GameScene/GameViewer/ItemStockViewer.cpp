//=============================================================================
//
// �X�g�b�N�r���A�[���� [ItemStockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "ItemStockViewer.h"

#include "../../../../main.h"
#include "../../Framework/BaseViewer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ItemStockViewer::ItemStockViewer()
{
	//����
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
	num->size = D3DXVECTOR3(84.0f, 84.0f, 0.0f);;
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.430f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	num->intervalPosScr = 42.0f;
	num->intervalPosTex = 0.10f;
	num->placeMax = 2;
	num->baseNumber = 10;
	num->isHopped = false;
	num->radian = 0;
	num->MakeVertex();

	//�X�g�b�N�A�C�R��
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Drill.png");
	icon->size = D3DXVECTOR3(360.0f, 300.0f, 0.0f);
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.7f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->MakeVertex();

	//�A�j���[�V����
	anim = new ViewerAnimater();
	std::vector<std::function<void()>> vec = {
		[=] {
		//�z�b�s���O
		anim->Hop(*num, D3DXVECTOR2(84.0f, 84.0f),D3DXVECTOR2(0.0f,30.0f), 15.0f);
	} };
	anim->SetAnimBehavior(vec);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ItemStockViewer::~ItemStockViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(icon);
	SAFE_DELETE(anim);
}

//=============================================================================
// �X�V����
//=============================================================================
void ItemStockViewer::Update(void)
{
	if (!isCurrentEqualLast((float)parameterBox)) isPlaying = true;
	if (!isPlaying) return;
	anim->PlayAnim([=]
	{
		anim->SetPlayFinished(isPlaying);
	});
}

//=============================================================================
// �`�揈��
//=============================================================================
void ItemStockViewer::Draw(void)
{
	//�A�C�R��
	icon->Draw();

	//����
	num->DrawCounter(num->baseNumber, parameterBox, num->placeMax,
		num->intervalPosScr, num->intervalPosTex);
}
