//=============================================================================
//
// ���O���̓��[���������� [NameEntryReelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Input/input.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "NameEntryReelViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryReelViewer::NameEntryReelViewer():
	character()
{
	//���[���̍��W�Ԋu
	const float intervalReelPos = 130.0f;

	//���[��
	for (int i = 0; i < entryNameMax; i++)
	{
		reel[i] = new BaseViewerDrawer();
		reel[i]->LoadTexture("data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/Character.png");
		reel[i]->size = D3DXVECTOR3(180.0f, 180.0f, 0.0f);
		reel[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		reel[i]->position = D3DXVECTOR3(SCREEN_CENTER_X + i* intervalReelPos, SCREEN_CENTER_Y, 0.0f);
		reel[i]->MakeVertex();
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