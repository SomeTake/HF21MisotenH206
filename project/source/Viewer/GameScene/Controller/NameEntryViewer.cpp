//=============================================================================
//
// ���O�o�^�r���A�[�R���g���[������ [NameEntryViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../NameEntryViewer/NameEntryReelViewer.h"
#include "../NameEntryViewer/NameEntryInput.h"
#include "../NameEntryViewer/NameEntryBgViewer.h"

#include "NameEntryViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
NameEntryViewer::NameEntryViewer() :
	entryNameID(),
	reelCnt()
{
	input = new NameEntryInput();

	nameEntryViewer.push_back(bgViewer = new NameEntryBgViewer());
	nameEntryViewer.push_back(reelViewer = new NameEntryReelViewer());
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

//*****************************************************************************
// ����������
//*****************************************************************************
void NameEntryViewer::Init(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		entryNameID[i] = 0;
	}

	reelCnt = 0;
}

//=============================================================================
// �X�V����
//=============================================================================
void NameEntryViewer::Update()
{
	//if (!isActive)
	//	return;

#ifdef _DEBUG
	for (int i = 0; i < entryNameMax; i++)
	{
		Debug::Text("nameID%d", entryNameID[i]);
	}
	if (Keyboard::GetTrigger(DIK_2))
	{
		SlideNameEntryViewer(true);
	}
	if (Keyboard::GetTrigger(DIK_3))
	{
		SlideNameEntryViewer(false);
	}

#endif

	MoveCursor();
	UpDownReel();
	SetEntryName();

	for (unsigned int i = 0; i < nameEntryViewer.size(); i++)
	{
		nameEntryViewer[i]->Update();
	}

	//ID�i�[
	for (int i = 0; i < entryNameMax; i++)
	{
		entryNameID[i] = reelViewer->GetReelChar()[i];
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void NameEntryViewer::Draw(void)
{
	//if (!isActive)
	//	return;

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
		//����������
		for (int i = 0; i < entryNameMax; i++)
		{
			entryNameID[i] = 0;
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
		reelCnt++;
		reelViewer->MoveCursorRight();
	}

	//���{�^���������ꂽ
	if (input->GetCursorLeft())
	{
		if (reelCnt <= 0) return;
		reelCnt--;
		reelViewer->MoveCursorLeft();
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
// �`��۔���̃Q�b�g
//=============================================================================
bool NameEntryViewer::GetIsActive()
{
	return isActive;
}

//=============================================================================
// �o�^��ID�擾�����i�����e�[�u����0�`35�܂ł̒l��entryNameMax�̔z��j
//=============================================================================
std::string NameEntryViewer::GetEntryNameID()
{
	std::string NameStr;
	NameStr += IntToString(entryNameID[0]);
	NameStr += IntToString(entryNameID[1]);
	NameStr += IntToString(entryNameID[2]);
	return NameStr;
}

//=============================================================================
// int�^�̃l�[����string�^�ɕϊ�
//=============================================================================
std::string NameEntryViewer::IntToString(int NameInt)
{
	if (NameInt >= 0 && NameInt < 10)
	{
		return "0" + std::to_string(NameInt);
	}
	else if (NameInt >= 10)
	{
		return std::to_string(NameInt);
	}

	return "00";
}

//=============================================================================
// ���O�o�^�r���A�[�̃X���C�h����
//=============================================================================
void NameEntryViewer::SlideNameEntryViewer(bool isIn)
{
	if (isIn)
	{
		bgViewer->SetBgIn([=]
		{
			reelViewer->SetTelopIn();
		});
	}
	else
	{
		bgViewer->SetBgOut();
		reelViewer->SetTelopOut();
	}
}
