//=============================================================================
//
// ���O�o�^�r���A�[�R���g���[������ [NameEntryViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../NameEntryViewer/NameEntryReelViewer.h"
#include "../NameEntryViewer/NameEntryCursorViewer.h"
#include "../NameEntryViewer/NameEntryInput.h"
#include "NameEntryViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryViewer::NameEntryViewer():
	entryName(),
	reelCnt()
{
	input = new NameEntryInput();

	nameEntryViewer.push_back(reelViewer = new NameEntryReelViewer());
	nameEntryViewer.push_back(cursorViewer = new NameEntryCursorViewer());
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
NameEntryViewer::~NameEntryViewer()
{
	SAFE_DELETE(input);

	//�����������
	for (unsigned int i = 0; i < nameEntryViewer.size(); i++)
	{
		SAFE_DELETE(nameEntryViewer[i]);
	}

	//�C���X�^���X����ꂽ�z����N���A
	nameEntryViewer.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryViewer::Update()
{
	if (!isActive)
		return;

#ifdef _DEBUG
	Debug::Text(entryName.c_str());
#endif

	MoveCursor();
	UpDownReel();
	SetEntryName();

	for (unsigned int i = 0; i < nameEntryViewer.size(); i++)
	{
		nameEntryViewer[i]->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryViewer::Draw(void)
{
	if (!isActive)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < nameEntryViewer.size(); i++)
	{
		nameEntryViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �o�^���Z�b�g����
//=============================================================================
void NameEntryViewer::SetEntryName()
{
	//�G���^�[�{�^���������ꂽ
	if (input->GetFinishedEntry())
	{
		const int charTypeMax = 36;

		//�����e�[�u��
		std::string charTable[charTypeMax] =
		{
			"A","B","C","D","E","F",
			"G","H","I","J","K","L",
			"M","N","O","P","Q","R",
			"S","T","U","V","W","X",
			"Y","Z","!","?","*",".",
			"/","\\","#","\"","%%","&"
		};

		entryName = {};

		for (int i = 0; i < entryNameMax; i++)
		{
			int id = reelViewer->GetReelChar()[i];
			entryName += charTable[id];
		}
	}
}

//=============================================================================
// �J�[�\���r���A�[�ړ�����
//=============================================================================
void NameEntryViewer::MoveCursor()
{
	//�E�{�^���������ꂽ
	if (input->GetCursorRight())
	{
		if (reelCnt >= entryNameMax - 1) return;
		cursorViewer->MoveCursorRight();
		reelCnt++;
	}

	//���{�^���������ꂽ
	if (input->GetCursorLeft())
	{
		if (reelCnt <= 0) return;
		cursorViewer->MoveCursorLeft();
		reelCnt--;
	}
}

//=============================================================================
// ���[���r���A�[�㉺�ړ�����
//=============================================================================
void NameEntryViewer::UpDownReel()
{
	//��{�^���������ꂽ
	if (input->GetReelUp())
	{
		reelViewer->ReelUp(reelCnt);
	}
	//���{�^���������ꂽ
	if (input->GetReelDown())
	{
		reelViewer->ReelDown(reelCnt);
	}
}

//=============================================================================
// �`��۔���̃Z�b�g
//=============================================================================
void NameEntryViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=============================================================================
// �o�^���擾����
//=============================================================================
std::string NameEntryViewer::GetEntryName()
{
	return entryName;
}