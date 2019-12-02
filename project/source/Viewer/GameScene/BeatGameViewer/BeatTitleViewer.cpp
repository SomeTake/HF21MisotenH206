//=============================================================================
//
// �A�ŃQ�[���^�C�g���r���A�[���� [BeatTitleViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "BeatTitleViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BeatTitleViewer::BeatTitleViewer()
{
	//�e�L�X�g
	title = new BaseViewerDrawer();
	title->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTitleViewer/Title.png");
	title->size = D3DXVECTOR3(1000.0f, 250.0f, 0.0f);
	title->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	title->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT /12, 0.0f);
	title->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BeatTitleViewer::~BeatTitleViewer()
{
	SAFE_DELETE(title);
}

//=============================================================================
// �X�V����
//=============================================================================
void BeatTitleViewer::Update()
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void BeatTitleViewer::Draw(void)
{
	//�^�C�g��
	title->Draw();
}

//=============================================================================
// �e�N�X�`�����󂯓n������
//=============================================================================
void BeatTitleViewer::SetTexture(TitleID id)
{
	//�e�L�X�g���Z�b�g
	title->SetTexture(1, Max, id);
}

//=============================================================================
// �e���b�v�Z�b�g����
//=============================================================================
void BeatTitleViewer::Set(TitleID id)
{
	//�e�N�X�`�����Z�b�g
	SetTexture(id);
}
