//=============================================================================
//
// �J�E���g�r���A�[�`��p���� [CountViewerDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "source/Viewer/Framework/ViewerDrawer/CountViewerDrawer.h"

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�@�i�J�E���^�[��p�j
//=============================================================================
void CountViewerDrawer::SetVertex(int placeCount, float placeInterval)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(size.x, size.y, 0.0f);
}

//=============================================================================
//�I�u�W�F�N�g�̃e�N�X�`�����W�ݒ菈���@�i�J�E���^�[��p�j
//=============================================================================
void CountViewerDrawer::SetTexture(int number, float placeInterval)
{
	// ���_���W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(number * placeInterval, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(number * placeInterval, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 1.0f);
}

//=============================================================================
//�J�E���^�[�`�揈��
//=============================================================================
void CountViewerDrawer::DrawCounter(int baseNumber, int parameterBox, int placeMax, float intervalNumberScr, float intervalNumberTex)
{
	for (int nCntPlace = 0; nCntPlace < placeMax; nCntPlace++)
	{
		int num;

		num = parameterBox % (int)(pow(baseNumber, (placeMax - nCntPlace)))
			/ (int)(pow(baseNumber, (placeMax - nCntPlace - 1)));

		Draw();
		SetVertex(nCntPlace, intervalNumberScr);
		SetTexture(num, intervalNumberTex);
	}
}
