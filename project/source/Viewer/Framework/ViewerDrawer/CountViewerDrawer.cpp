//=============================================================================
//
// �J�E���g�r���A�[�`��p���� [CountViewerDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include"../../../../main.h"
#include "CountViewerDrawer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CountViewerDrawer::CountViewerDrawer()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CountViewerDrawer::~CountViewerDrawer()
{
}

//=============================================================================
// ���_���W�̐ݒ�@�i�J�E���^�[��p�j
//=============================================================================
void CountViewerDrawer::SetVertexPos(int placeCount, float placeInterval)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, 0.0f) 
		+ D3DXVECTOR3(-size.x/2, -size.y/2, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, 0.0f) 
		+ D3DXVECTOR3(size.x/2, -size.y/2, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, 0.0f) 
		+ D3DXVECTOR3(-size.x/2, size.y/2, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, 0.0f) 
		+ D3DXVECTOR3(size.x/2, size.y/2, 0.0f);
}

//=============================================================================
//�I�u�W�F�N�g�̃e�N�X�`�����W�ݒ菈���@�i�J�E���^�[��p�j
//=============================================================================
void CountViewerDrawer::SetTexture(int number, float placeInterval)
{
	// ���_���W�̐ݒ�
	float sizeX = 1.0f / texDivX;
	float sizeY = 1.0f / texDivY;
	int x = number % texDivX;
	int y = number / texDivX;

	vertexWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vertexWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vertexWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vertexWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
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

		this->Draw();
		SetVertexPos(nCntPlace, intervalNumberScr);
		SetTexture(num, intervalNumberTex);
	}
}

//=============================================================================
// �����z�b�s���O����
//=============================================================================
float CountViewerDrawer::HopNumber(float sizeY, float initSizeY, float hopValue)
{
	if (isHopped == true)
	{
		sizeY = initSizeY + (hopValue * sinf(radian));
		if (radian >= D3DX_PI)
		{
			radian = 0.0f;
			isHopped = false;
		}
		radian += hopSpeed;
	}

	return sizeY;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CountViewerDrawer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}
