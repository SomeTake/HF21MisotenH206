//=============================================================================
//
// ��������r���[�A���� [OperationExplanationViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "OperationExplanationViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
OperationExplanationViewer::OperationExplanationViewer() :
	active(true)
{
	//�e�L�X�g
	const D3DXVECTOR3 Size = { 250.0f, 62.5f, 0.0f };
	const D3DXVECTOR3 BasePosition = { SCREEN_CENTER_X - Size.x * 1.5f, 960.0f, 0.0f };
	for (int i = 0; i < textMax; i++)
	{

		text[i] = new BaseViewerDrawer();
		text[i]->LoadTexture("data/TEXTURE/Viewer/FieldViewer/OperationExplanationViewer/OperationExplanation.png");
		text[i]->size = Size;
		text[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVECTOR3 position = BasePosition;
		position.x += Size.x * i;
		text[i]->position = position;
		text[i]->MakeVertex();

		//����̃Z�b�g�܂œ����ɂ��Ă���
		text[i]->SetAlpha(0.0f);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
OperationExplanationViewer::~OperationExplanationViewer()
{
	for (int i = 0; i < textMax; i++)
	{
		SAFE_DELETE(text[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void OperationExplanationViewer::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void OperationExplanationViewer::Draw(void)
{
	if (!active)
		return;

	for (int i = 0; i < textMax; i++)
	{
		text[i]->Draw();
	}
}

//=============================================================================
// �e�N�X�`��UV�Z�b�g����
//=============================================================================
void OperationExplanationViewer::SetTexture(OperationID id0, OperationID id1, OperationID id2, OperationID id3)
{
	//id���i�[���Ă����z��
	OperationID id[textMax] = {
		id0,
		id1,
		id2,
		id3
	};

	for (int i = 0; i < textMax; i++)
	{
		//ID�̎�ސ��ł͂Ȃ����ۂ̃e�N�X�`�����̃e�L�X�g�̎�ނŃZ�b�g
		//�\�����Ȃ��I�y���[�V�����Ȃ瓧���ɂ��Ă���
		if (id[i] < Z_None)
		{
			const int textTypeMax = 7;

			//�e�L�X�g�̃e�N�X�`��UV��ύX
			text[i]->SetTexture(1, textTypeMax, id[i]);

			//�\������
			text[i]->SetAlpha(1.0f);
		}
		else
		{
			//�����ɂ��Ă���
			text[i]->SetAlpha(0.0f);
		}
	}
}

//=============================================================================
// ��������r���A�[�̃Z�b�g����
//=============================================================================
void OperationExplanationViewer::Set(OperationID id0, OperationID id1, OperationID id2, OperationID id3)
{
	//�e�N�X�`�����󂯓n������
	SetTexture(id0, id1, id2, id3);
}

//=============================================================================
// �A�N�e�B�u�ݒ�
//=============================================================================
void OperationExplanationViewer::SetActive(bool state)
{
	active = state;
}
