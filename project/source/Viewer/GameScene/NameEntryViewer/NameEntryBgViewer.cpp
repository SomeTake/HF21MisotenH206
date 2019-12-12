//=============================================================================
//
// ���O���͔w�i���� [NameEntryBgViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryBgViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryBgViewer::NameEntryBgViewer() :
	sholudDraw(false)
{
	congratsText = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT/2.50f),
		D3DXVECTOR2(900.0f, 900/8.0f), "data/TEXTURE/Viewer/NameEntryViewer/NameEntryBgViewer/CongratsText.png");
	
	newRecordText = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 2.10f), 
		D3DXVECTOR2(600.0f, 600 / 8.0f),"data/TEXTURE/Viewer/NameEntryViewer/NameEntryBgViewer/NewRecordText.png");

	crown = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 3.0f), 
		D3DXVECTOR2(300.0f, 300.0f),"data/TEXTURE/Viewer/NameEntryViewer/NameEntryBgViewer/Crown.png");

	anim = new ViewerAnimater();
	std::vector<std::function<void()>> vec = {[=]
	{
		anim->Hop(*crown,D3DXVECTOR2(300.0f, 300.0f),D3DXVECTOR2(75.0f,75.0f),30.0f,[=]
		{
			anim->SubHop(*newRecordText,D3DXVECTOR2(600.0f, 600 / 8.0f),D3DXVECTOR2(150.0f, 150 / 8.0f),30.0f,[=]
			{
				anim->SubHop(*congratsText,D3DXVECTOR2(900.0f, 900 / 8.0f),D3DXVECTOR2(225.0f, 225 / 8.0f),30.0f);
			});
		});
	} };
	anim->SetAnimBehavior(vec);

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
	SAFE_DELETE(anim);
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryBgViewer::Update(void)
{
	if(!isPlaying) return;
	anim->PlayAnim([=]
	{
		anim->SetPlayFinished(isPlaying, [=]
		{
			this->Callback();
		});
	});
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryBgViewer::Draw(void)
{
	if (!sholudDraw) return;
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

//=============================================================================
// �w�i�X�N���[���C���Z�b�g����
//=============================================================================
void NameEntryBgViewer::SetBgIn(std::function<void()> Callback)
{
	this->Callback = Callback;
	sholudDraw = true;
	isPlaying = true;
}

//=============================================================================
// �w�i�X�N���[���A�E�g�Z�b�g����
//=============================================================================
void NameEntryBgViewer::SetBgOut()
{
	sholudDraw = false;
}