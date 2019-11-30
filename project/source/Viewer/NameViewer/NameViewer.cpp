//=====================================
//
// �l�[���r���A�[[NameViewer.cpp]
// �@�\�F���O�\���p
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "NameViewer.h"

//=====================================
// �R���X�g���N�^
//=====================================
NameViewer::NameViewer()
{
	for (int i = 0; i < NumChar; i++)
	{
		polygon[i] = new Polygon2D();
		polygon[i]->LoadTexture("data/TEXTURE/Alphabet/nameChar01.png");
	}
}

//=====================================
// �f�X�g���N�^
//=====================================
NameViewer::~NameViewer()
{
	for (int i = 0; i < NumChar; i++)
	{
		SAFE_DELETE(polygon[i]);
	}
}

//=====================================
// �X�V
//=====================================
void NameViewer::Update()
{
	polygon[0]->SetPosition(stdPosition + D3DXVECTOR3(-interval, 0.0f, 0.0f));
	polygon[1]->SetPosition(stdPosition);
	polygon[2]->SetPosition(stdPosition + D3DXVECTOR3(interval, 0.0f, 0.0f));
}

//=====================================
// �`��
//=====================================
void NameViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (int i = 0; i < NumChar; i++)
	{
		polygon[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// �����ݒ�
//=====================================
void NameViewer::Init(const D3DXVECTOR3 & pos, const D3DXVECTOR2 & size)
{
	SetSize(size.x, size.y);
	SetPosition(pos);
}

//=====================================
// ���O�̃Z�b�g
//=====================================
void NameViewer::SetName(int * Buff)
{
	for (int i = 0; i < NumChar; i++, Buff++)
	{
		int x = *Buff % DivideX;
		int y = *Buff / DivideX;
		float left = (float)x * Width;
		float top = (float)y * Height;
		polygon[i]->SetUV(left, top, Width, Height);
	}
}

//=====================================
// ���W�Z�b�g
//=====================================
void NameViewer::SetPosition(const D3DXVECTOR3 & pos)
{
	stdPosition = pos;
}

//=====================================
// �T�C�Y�Z�b�g
//=====================================
void NameViewer::SetSize(const float & x, const float & y)
{
	for (int i = 0; i < NumChar; i++)
	{
		polygon[i]->SetSize(x, y);
	}
	interval = x * 2;
}
