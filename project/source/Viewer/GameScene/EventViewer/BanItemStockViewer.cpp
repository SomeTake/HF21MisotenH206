//=============================================================================
//
// �o���X�g�b�N�r���A�[���� [BanItemStockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "../../../../Framework/Math/Easing.h"
#include "BanItemStockViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BanItemStockViewer::BanItemStockViewer()
{
	//�o�c�A�C�R��
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/EventViewer/BanStockViewer/BanStock.png");
	icon->size = D3DXVECTOR3(400.0f, 400.0f, 0.0f);
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.5f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BanItemStockViewer::~BanItemStockViewer()
{
	SAFE_DELETE(icon);
}

//=============================================================================
// �X�V����
//=============================================================================
void BanItemStockViewer::Update(void)
{
	//�A�j���[�V����
	Play();
}

//=============================================================================
// �`�揈��
//=============================================================================
void BanItemStockViewer::Draw(void)
{
	//�X�g�b�N�o�����Ȃ�`��`��
	if (parameterBox == true) return;

	icon->Draw();
}

//=============================================================================
// �A�j���[�V��������
//=============================================================================
void BanItemStockViewer::Play(void)
{

}
