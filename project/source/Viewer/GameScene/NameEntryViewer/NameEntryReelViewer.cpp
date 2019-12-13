//=============================================================================
//
// ���O���̓��[���������� [NameEntryReelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryReelViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include"../../Framework/ViewerAnimater/ViewerAnimater.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//���[���̍��W�Ԋu
static const float intervalReelPos = 166.50f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryReelViewer::NameEntryReelViewer() :
	isInPlaying(false),
	isOutPlaying(false)
{
	const D3DXVECTOR2 cursorPos = { SCREEN_WIDTH / 10 * 6.6250f, SCREEN_HEIGHT / 1.520f };
	const D3DXVECTOR2 bgPos = { SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 1.250f };
	const D3DXVECTOR2 textPos = { (int)(SCREEN_WIDTH / 10 * 7.50f), (int)(SCREEN_HEIGHT / 1.250f) };
	const D3DXVECTOR2 underBarPos = { (int)(SCREEN_WIDTH / 10 * 7.50f), (int)(SCREEN_HEIGHT / 1.45f) };
	const float animStartPosX = SCREEN_WIDTH * 1.50f;

	for (int i = 0; i < entryNameMax; i++)
	{
		reel[i] = new BaseViewerDrawer(D3DXVECTOR2(animStartPosX + i * intervalReelPos, SCREEN_HEIGHT / 1.520f),
			D3DXVECTOR2(180.0f, 180.0f), "data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/Character.png");
		reel[i]->SetTexture(6, 6, 0);
	}

	cursor = new BaseViewerDrawer(D3DXVECTOR2(animStartPosX, cursorPos.y),
		D3DXVECTOR2(150.0f, 150.0f), "data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/Cursor.png");

	bg = new BaseViewerDrawer(D3DXVECTOR2(animStartPosX, bgPos.y), D3DXVECTOR2(600.0f, 512.0f / 4),
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/BG.png");

	text = new TextViewer("data/FONT/Makinas-4-Square.otf", 50);
	text->SetPos((int)(animStartPosX), (int)textPos.y);
	text->SetText("���O����͂��Ă�");

	underBar = new TextViewer("data/FONT/Makinas-4-Square.otf", 100);
	underBar->SetPos((int)(animStartPosX), (int)underBarPos.y);
	underBar->SetText("�Q�@�Q�@�Q");

	anim[AnimScene::TelopIn] = new ViewerAnimater();
	std::vector<std::function<void()>> inVec = { [=]
	{
		InReel([=]
		{
			anim[AnimScene::TelopIn]->SubMove(*cursor, D3DXVECTOR2(animStartPosX, cursorPos.y),cursorPos,OutCirc,[=]
			{
				anim[AnimScene::TelopIn]->SubMove(*bg, D3DXVECTOR2(animStartPosX, bgPos.y),bgPos,OutCirc);
			});
		});
	}
	};
	anim[AnimScene::TelopIn]->SetAnimBehavior(inVec);

	anim[AnimScene::TelopOut] = new ViewerAnimater();
	std::vector<std::function<void()>> outVec = { [=]
	{
		OutReel([=]
		{
			anim[AnimScene::TelopOut]->SubMove(*cursor,cursorPos,D3DXVECTOR2(animStartPosX, cursorPos.y),InCirc,[=]
			{
				anim[AnimScene::TelopOut]->SubMove(*bg,bgPos,D3DXVECTOR2(animStartPosX, bgPos.y),InCirc);
			});
		});
	}
	};
	anim[AnimScene::TelopOut]->SetAnimBehavior(outVec);
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
	SAFE_DELETE(cursor);
	SAFE_DELETE(bg);
	SAFE_DELETE(text);
	SAFE_DELETE(underBar);
	SAFE_DELETE(anim[AnimScene::TelopIn]);
	SAFE_DELETE(anim[AnimScene::TelopOut]);
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryReelViewer::Update(void)
{
	if (isInPlaying)
	{
		anim[AnimScene::TelopIn]->PlayAnim([=]
		{
			anim[AnimScene::TelopIn]->SetPlayFinished(isInPlaying);
		});
	}
	if (isOutPlaying)
	{
		anim[AnimScene::TelopOut]->PlayAnim([=]
		{
			anim[AnimScene::TelopOut]->SetPlayFinished(isOutPlaying);
		});
	}
	text->SetPos((int)bg->position.x, (int)bg->position.y);
	underBar->SetPos((int)bg->position.x, (int)(SCREEN_HEIGHT / 1.45f));
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryReelViewer::Draw(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		reel[i]->Draw();
	}
	cursor->Draw();
	bg->Draw();
	text->Draw();
	underBar->Draw();
}

//=============================================================================
// ���[���̃X�N���[���C������
//=============================================================================
void NameEntryReelViewer::InReel(std::function<void()> Callback)
{
	const float animStartPosX = SCREEN_WIDTH * 1.50f;
	int index = 0;
	anim[AnimScene::TelopIn]->Move(*reel[index], D3DXVECTOR2(animStartPosX, reel[index]->position.y),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y), 20.0f, OutCirc, [=]
	{
		int index = 1;
		anim[AnimScene::TelopIn]->SubMove(*reel[index], D3DXVECTOR2(animStartPosX, reel[index]->position.y),
			D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y), OutCirc, [=]
		{
			int index = 2;
			anim[AnimScene::TelopIn]->SubMove(*reel[index], D3DXVECTOR2(animStartPosX, reel[index]->position.y),
				D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y), OutCirc, [=]
			{
				Callback();
			});
		});
	});
}

//=============================================================================
// ���[���̃X�N���[���A�E�g����
//=============================================================================
void NameEntryReelViewer::OutReel(std::function<void()> Callback)
{
	const float animStartPosX = SCREEN_WIDTH * 1.50f;
	int index = 0;
	anim[AnimScene::TelopOut]->Move(*reel[index], D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y),
		D3DXVECTOR2(animStartPosX, reel[index]->position.y), 20.0f, InCirc, [=]
	{
		int index = 1;
		anim[AnimScene::TelopOut]->SubMove(*reel[index], D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y),
			D3DXVECTOR2(animStartPosX, reel[index]->position.y), InCirc, [=]
		{
			int index = 2;
			anim[AnimScene::TelopOut]->SubMove(*reel[index], D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y),
				D3DXVECTOR2(animStartPosX, reel[index]->position.y), InCirc, [=]
			{
				Callback();
			});
		});
	});
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
// �J�[�\���E�ړ�����
//=============================================================================
void NameEntryReelViewer::MoveCursorRight(void)
{
	cursor->position.x += intervalReelPos;
}

//=============================================================================
// �J�[�\�����ړ�����
//=============================================================================
void NameEntryReelViewer::MoveCursorLeft(void)
{
	cursor->position.x -= intervalReelPos;
}

//=============================================================================
// ���[���̕������擾���鏈��
//=============================================================================
int* NameEntryReelViewer::GetReelChar()
{
	return character;
}

//=============================================================================
// �e���b�v�X�N���[���C������
//=============================================================================
void NameEntryReelViewer::SetTelopIn()
{
	for (int i = 0; i < entryNameMax; i++)
	{
		//�����񏉊���
		character[i] = 0;
		// UV�̏�����
		reel[i]->SetTexture(6, 6, 0);
	}

	isInPlaying = true;
}

//=============================================================================
// �e���b�v�X�N���[���A�E�g����
//=============================================================================
void NameEntryReelViewer::SetTelopOut()
{
	isOutPlaying = true;
}