//=============================================================================
//
// ���U���g���O���͏������� [ResultNameEntryViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Input/input.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "ResultNameEntryViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static const float intervalPos = 130.0f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ResultNameEntryViewer::ResultNameEntryViewer():
	charID(),
	charCnt(),
	entryName()
{
	//����
	for (int i = 0; i < entryNameMax; i++)
	{
		character[i] = new BaseViewerDrawer();
		character[i]->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultNameEntryViewer/Character.png");
		character[i]->size = D3DXVECTOR3(180.0f, 180.0f, 0.0f);
		character[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		character[i]->position = D3DXVECTOR3(SCREEN_CENTER_X + i* intervalPos, SCREEN_CENTER_Y, 0.0f);
		character[i]->MakeVertex();
		character[i]->SetTexture(6, 6, 0);
	}

	//�J�[�\��
	cursor = new BaseViewerDrawer();
	cursor->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultNameEntryViewer/Cursor.png");
	cursor->size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	cursor->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	cursor->MakeVertex();
	cursor->SetTexture(2, 2, 0);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ResultNameEntryViewer::~ResultNameEntryViewer()
{
	for (int i = 0; i < entryNameMax; i++)
	{
		SAFE_DELETE(character[i]);
	}

	SAFE_DELETE(cursor);
}

//=============================================================================
// �X�V����
//=============================================================================
void ResultNameEntryViewer::Update(void)
{
	//���O���͏���
	NameInput();

	//�e�N�X�`��UV�Z�b�g����
	SetTexture();

	//�J�[�\���̍��W���Z�b�g
	SetCursorPos();

	Debug::Text(entryName.c_str());
}

//=============================================================================
// �`�揈��
//=============================================================================
void ResultNameEntryViewer::Draw(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		//�w�i���ɕ`��
		character[i]->Draw();
	}

	cursor->Draw();
}

//=============================================================================
// �e�N�X�`�����󂯓n������
//=============================================================================
void ResultNameEntryViewer::SetTexture()
{
	//�����Ղ̃e�N�X�`��UV��ύX
	character[charCnt]->SetTexture(6, 6, charID[charCnt]);
}

//=============================================================================
// ���O���͏���
//=============================================================================
void ResultNameEntryViewer::NameInput()
{
	//��{�^���������ꂽ
	if (Keyboard::GetTrigger(DIK_UP))
	{
		if (charID[charCnt] > 0)
			charID[charCnt]--;
		else
			charID[charCnt] = charTypeMax-1;
	}
	//���{�^���������ꂽ
	if (Keyboard::GetTrigger(DIK_DOWN))
	{
		if (charID[charCnt] < charTypeMax-1)
			charID[charCnt]++;
		else
			charID[charCnt] = 0;
	}
	//���{�^���������ꂽ
	if (Keyboard::GetTrigger(DIK_LEFT))
	{
		if (charCnt > 0)
			charCnt--;
	}
	//�E�{�^���������ꂽ
	if (Keyboard::GetTrigger(DIK_RIGHT))
	{
		if (charCnt < entryNameMax-1)
			charCnt++;
	}
	//�G���^�[�{�^���������ꂽ
	if (Keyboard::GetTrigger(DIK_RETURN))
	{
		entryName = {};

		for (int i = 0; i < entryNameMax; i++)
		{
			SetEntryName(charID[i]);
		}
	}
}

//=============================================================================
// �o�^���Z�b�g����
//=============================================================================
void ResultNameEntryViewer::SetEntryName(int id)
{
	std::string charTable[charTypeMax] =
	{
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"!",
		"?",
		"*",
		".",
		"/",
		"\\",
		"#",
		"\"",
		"%%",
		"&"
	};

	entryName += charTable[id];
}

//=============================================================================
// �J�[�\�����W�Z�b�g����
//=============================================================================
void ResultNameEntryViewer::SetCursorPos()
{
	cursor->position.x = SCREEN_CENTER_X + charCnt * intervalPos;
}
//=============================================================================
// �o�^���擾����
//=============================================================================
std::string ResultNameEntryViewer::GetEntryName(void)
{
	return entryName;
}