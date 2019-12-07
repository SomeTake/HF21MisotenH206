//=============================================================================
//
// ���O���̓��[���������� [NameEntryBgViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryBgViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryBgViewer::NameEntryBgViewer()
{
	//���[���̍��W�Ԋu
	const float intervalReelPos = 130.0f;

	congratsText = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.0f, SCREEN_HEIGHT/2.50f),D3DXVECTOR2(900.0f, 900/8.0f), 
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryBgViewer/CongratsText.png");

	congratsText->SetTexture(1,8, 0);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
NameEntryBgViewer::~NameEntryBgViewer()
{
	for (int i = 0; i < entryNameMax; i++)
	{
		SAFE_DELETE(congratsText);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryBgViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryBgViewer::Draw(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		//�w�i���ɕ`��
		congratsText->Draw();
	}
}