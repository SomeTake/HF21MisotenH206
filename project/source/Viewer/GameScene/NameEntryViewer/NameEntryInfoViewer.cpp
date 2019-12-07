//=============================================================================
//
// ���O���͔w�i���� [NameEntryInfoViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryInfoViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryInfoViewer::NameEntryInfoViewer()
{
	bg = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 1.30f), D3DXVECTOR2(600.0f, 512.0f/4),
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryInfoViewer/BG.png");

	text = new TextViewer("data/FONT/Makinas-4-Square.otf", 50);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 7.50f), (int)(SCREEN_HEIGHT / 1.30f));
	text->SetText("���O����͂��Ă�");
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
NameEntryInfoViewer::~NameEntryInfoViewer()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(text);
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryInfoViewer::Update(void)
{
	FadeText();
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryInfoViewer::Draw(void)
{
	bg->Draw();
	text->Draw();
}

//=============================================================================
// �t�F�[�h����
//=============================================================================
void NameEntryInfoViewer::FadeText()
{
	alpha+= 0.03f;
	text->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	alpha = Math::WrapAround(0.0f, 1.0f, alpha);
}
