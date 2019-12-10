//=============================================================================
//
// ���O���͔w�i���� [NameEntryInfoViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryInfoViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryInfoViewer::NameEntryInfoViewer()
{
	bg = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 1.250f), D3DXVECTOR2(600.0f, 512.0f/4),
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryInfoViewer/BG.png");

	text = new TextViewer("�}�L�i�X 4 Square", 50);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 7.50f), (int)(SCREEN_HEIGHT / 1.250f));
	text->SetText("���O����͂��Ă�");

	underBar = new TextViewer("�}�L�i�X 4 Square", 100);
	underBar->SetPos((int)(SCREEN_WIDTH / 10 * 7.50f), (int)(SCREEN_HEIGHT / 1.5f));
	underBar->SetText("�Q�@�Q�@�Q");
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
NameEntryInfoViewer::~NameEntryInfoViewer()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(text);
	SAFE_DELETE(underBar);
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryInfoViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryInfoViewer::Draw(void)
{
	bg->Draw();
	text->Draw();
	underBar->Draw();
}