//=============================================================================
//
// ���O���̓J�[�\���������� [NameEntryCursorViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Input/input.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "NameEntryCursorViewer.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//���[���̍��W�Ԋu
static const float intervalReelPos = 130.0f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryCursorViewer::NameEntryCursorViewer()
{
	//�J�[�\��
	cursor = new BaseViewerDrawer();
	cursor->LoadTexture("data/TEXTURE/Viewer/NameEntryViewer/NameEntryCursorViewer/Cursor.png");
	cursor->size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	cursor->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 7.0f, SCREEN_HEIGHT / 10 * 8.0f, 0.0f);
	cursor->MakeVertex();
	cursor->SetTexture(2, 2, 0);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
NameEntryCursorViewer::~NameEntryCursorViewer()
{
	SAFE_DELETE(cursor);
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryCursorViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryCursorViewer::Draw(void)
{
	cursor->Draw();
}

//=============================================================================
// �J�[�\�����W���E�Ɉړ�����
//=============================================================================
void NameEntryCursorViewer::MoveCursorRight()
{
	cursor->position.x += intervalReelPos;
}

//=============================================================================
// �J�[�\�����W�����Ɉړ�����
//=============================================================================
void NameEntryCursorViewer::MoveCursorLeft()
{
	cursor->position.x -= intervalReelPos;
}