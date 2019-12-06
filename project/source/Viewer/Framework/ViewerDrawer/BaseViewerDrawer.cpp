//=============================================================================
//
// ���r���A�[�`��p���� [BaseViewerDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include"../../../../main.h"
#include "../../../../Framework/Resource/ResourceManager.h"
#include "BaseViewerDrawer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
BaseViewerDrawer::BaseViewerDrawer(D3DXVECTOR2 position, D3DXVECTOR2 size, const char* path)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->size.x = size.x;
	this->size.y = size.y;

	LoadTexture(path);
	MakeVertex();
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
BaseViewerDrawer::BaseViewerDrawer()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
BaseViewerDrawer::~BaseViewerDrawer()
{
	SAFE_DELETE(texture);
}	

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void BaseViewerDrawer::LoadTexture(const char *path)
{
	ResourceManager::Instance()->GetTexture(path,texture);
}

//=============================================================================
// �I�u�W�F�N�g�`�揈��
//=============================================================================
void BaseViewerDrawer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	//���_���W���Z�b�g
	SetVertexPos();

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void BaseViewerDrawer::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	SetVertexPos();

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	SetColor(SET_COLOR_NOT_COLORED);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void BaseViewerDrawer::SetVertexPos()
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x/2, -size.y/2, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x/2, -size.y/2, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x/2, size.y/2, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x/2, size.y/2, 0.0f);
}

//=============================================================================
// �e�N�X�`�����W�ݒ菈��
//=============================================================================
void BaseViewerDrawer::SetTexture(int divX, int divY, int pattern)
{
	float sizeX = 1.0f / divX;
	float sizeY = 1.0f / divY;
	int x = pattern % divX;
	int y = pattern / divX;

	vertexWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vertexWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vertexWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1)* sizeY);
	vertexWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

//=============================================================================
// ���W�Z�b�g����
//=============================================================================
void BaseViewerDrawer::SetPosition(const D3DXVECTOR3 pos)
{
	this->position = pos;
}

//=============================================================================
//�I�u�W�F�N�g�̃A���t�@�l�ݒ菈���@�i���߁j
//=============================================================================
void BaseViewerDrawer::SetAlpha(float alpha)
{
	D3DXCOLOR c = vertexWk[3].diffuse;
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = D3DXCOLOR(c.r, c.g, c.b, alpha);
}

//=============================================================================
//�I�u�W�F�N�g�̔��ˌ��ݒ菈��
//=============================================================================
void BaseViewerDrawer::SetColor(D3DXCOLOR color)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = color;
}

//=============================================================================
// ���W�擾����
//=============================================================================
D3DXVECTOR3 BaseViewerDrawer::GetPosition(void)
{
	return position;
}

//=============================================================================
// �e�N�X�`���̃J���[�擾����
//=============================================================================
D3DXCOLOR BaseViewerDrawer::GetColor(void)
{
	return vertexWk[3].diffuse;
}
