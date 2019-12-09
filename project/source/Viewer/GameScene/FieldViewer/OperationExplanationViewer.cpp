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
OperationExplanationViewer::OperationExplanationViewer()
{
	//�e�L�X�g
	for  (int i = 0; i < textMax; i++)
	{
		text[i] = new BaseViewerDrawer();
		text[i]->LoadTexture("data/TEXTURE/Viewer/FieldViewer/OperationExplanationViewer/OperationExplanation.png");
		text[i]->size = D3DXVECTOR3(210.0f, 50.0f, 0.0f);
		text[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		text[i]->position = D3DXVECTOR3((float)(SCREEN_WIDTH/3 + (i*SCREEN_WIDTH/3/2)), SCREEN_CENTER_Y*1.8f, 0.0f);
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
	for (int i = 0; i < textMax; i++)
	{
		text[i]->Draw();
	}
}

//=============================================================================
// �e�N�X�`��UV�Z�b�g����
//=============================================================================
void OperationExplanationViewer::SetTexture(OperationID id0, OperationID id1, OperationID id2)
{
	//id���i�[���Ă����z��
	OperationID id[textMax] = {
		id0,
		id1,
		id2
	};

	for (int i = 0; i < textMax; i++)
	{
		//ID�̎�ސ��ł͂Ȃ����ۂ̃e�N�X�`�����̃e�L�X�g�̎�ނŃZ�b�g
		//�\�����Ȃ��I�y���[�V�����Ȃ瓧���ɂ��Ă���
		if (id[i] < Z_None)
		{
			const int textTypeMax = 5;

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
void OperationExplanationViewer::Set(OperationID id0, OperationID id1, OperationID id2)
{
	//�e�N�X�`�����󂯓n������
	SetTexture(id0,id1,id2);
}
