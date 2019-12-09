//=============================================================================
//
// ���O���͔w�i���� [NameEntryBgViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryBgViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryBgViewer::NameEntryBgViewer()
{
	congratsText = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT/2.50f),D3DXVECTOR2(900.0f, 900/8.0f), 
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryBgViewer/CongratsText.png");
	
	newRecordText = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 2.10f), D3DXVECTOR2(600.0f, 600 / 8.0f),
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryBgViewer/NewRecordText.png");

	crown = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 3.0f), D3DXVECTOR2(300.0f, 300.0f),
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryBgViewer/Crown.png");

	congratsText->SetTexture(1,8, 0);
	newRecordText->SetTexture(1, 8, 0);

	//�e�N�X�`���A�j���[�V�����^�X�N���쐬
	TaskManager::Instance()->CreatePeriodicTask(3, [=]
	{
		AnimTexture();
	});
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
NameEntryBgViewer::~NameEntryBgViewer()
{
	SAFE_DELETE(congratsText);
	SAFE_DELETE(newRecordText);
	SAFE_DELETE(crown);
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
	crown->Draw();
	congratsText->Draw();
	newRecordText->Draw();
}

//=============================================================================
// �e�N�X�`���A�j���[�V��������
//=============================================================================
void NameEntryBgViewer::AnimTexture(void)
{
	int texDivX = 1;
	int texDivY = 8;
	currentTexPattern++;

	congratsText->SetTexture(texDivX, texDivY, currentTexPattern);
	newRecordText->SetTexture(texDivX, texDivY, currentTexPattern);
}
