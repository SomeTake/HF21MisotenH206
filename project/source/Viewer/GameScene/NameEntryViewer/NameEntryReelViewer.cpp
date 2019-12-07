//=============================================================================
//
// ���O���̓��[���������� [NameEntryReelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryReelViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryReelViewer::NameEntryReelViewer():
	character()
{
	//���[���̍��W�Ԋu
	const float intervalReelPos = 165.0f;

	//���[��
	for (int i = 0; i < entryNameMax; i++)
	{
		reel[i] = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + i * intervalReelPos, SCREEN_HEIGHT / 1.520f),
			D3DXVECTOR2(180.0f, 180.0f), "data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/Character.png");
		reel[i]->SetTexture(6, 6, 0);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
NameEntryReelViewer::~NameEntryReelViewer()
{
	for (int i = 0; i < entryNameMax; i++)
	{
		SAFE_DELETE(reel[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryReelViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryReelViewer::Draw(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		//�w�i���ɕ`��
		reel[i]->Draw();
	}
}

//=============================================================================
// ���[���A�b�v����
//=============================================================================
void NameEntryReelViewer::ReelUp(int reelCnt)
{
	if (character[reelCnt] > 0)
		character[reelCnt]--;
	else
		character[reelCnt] = charTypeMax - 1;

	//���[���̃e�N�X�`��UV��ύX
	reel[reelCnt]->SetTexture(6, 6, character[reelCnt]);
}

//=============================================================================
// ���[���_�E������
//=============================================================================
void NameEntryReelViewer::ReelDown(int reelCnt)
{
	if (character[reelCnt] < charTypeMax - 1)
		character[reelCnt]++;
	else
		character[reelCnt] = 0;

	//���[���̃e�N�X�`��UV��ύX
	reel[reelCnt]->SetTexture(6, 6, character[reelCnt]);
}

//=============================================================================
// ���[���̕������擾���鏈��
//=============================================================================
int* NameEntryReelViewer::GetReelChar()
{
	return character;
}