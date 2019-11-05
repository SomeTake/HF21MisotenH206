//=============================================================================
//
// ��]�r���A�[�`��p���� [RotateViewerDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include"../../../../main.h"
#include "RotateViewerDrawer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
RotateViewerDrawer::RotateViewerDrawer()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
RotateViewerDrawer::~RotateViewerDrawer()
{
}

//=============================================================================
// �I�u�W�F�N�g�T�[�N���̍쐬�@�i��]�I�u�W�F�N�g�p�̃T�[�N�������j
//=============================================================================
void RotateViewerDrawer::CreateCircle()
{
	D3DXVECTOR2 temp = D3DXVECTOR2(size.x/2, size.y/2);
	radius = D3DXVec2Length(&temp);
	baseAngle = atan2f(size.y/2, size.x/2);
}

//=============================================================================
// ���_�̍쐬 (��]�I�u�W�F�N�g�p)
//=============================================================================
void RotateViewerDrawer::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�I�u�W�F�N�g�T�[�N���̍쐬
	CreateCircle();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx.x = position.x - cosf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.z = 0.0f;

	vertexWk[1].vtx.x = position.x + cosf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.z = 0.0f;

	vertexWk[2].vtx.x = position.x - cosf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.z = 0.0f;

	vertexWk[3].vtx.x = position.x + cosf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.z = 0.0f;

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	SetColor(SET_COLOR_NOT_COLORED);
}

//=============================================================================
// ���_���W�̐ݒ� (��]�I�u�W�F�N�g�p)
//=============================================================================
void RotateViewerDrawer::SetVertexPos()
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx.x = position.x - cosf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.z = 0.0f;

	vertexWk[1].vtx.x = position.x + cosf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.z = 0.0f;

	vertexWk[2].vtx.x = position.x - cosf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.z = 0.0f;

	vertexWk[3].vtx.x = position.x + cosf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.z = 0.0f;
}
