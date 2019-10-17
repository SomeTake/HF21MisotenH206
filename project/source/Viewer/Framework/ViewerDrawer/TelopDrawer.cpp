//=============================================================================
//
// �e���b�v�`��p���� [TelopDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include"../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "TelopDrawer.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//�w�i�J�Ԋu
static const float bgCloseOpenDuration = 15.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
TelopDrawer::TelopDrawer()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
TelopDrawer::~TelopDrawer()
{
}

//=============================================================================
// �w�i�e�N�X�`���̒��_�̍쐬
//=============================================================================
void TelopDrawer::MakeVertexBG()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(3.0, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(3.0f, 1.0f);
}

//=============================================================================
// �e�L�X�g�e�N�X�`���̒��_�̍쐬
//=============================================================================
void TelopDrawer::MakeVertexText()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);

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
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�
//=============================================================================
void TelopDrawer::SetVertex()
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);
}

//=============================================================================
// �w�i�̒��_���W�̐ݒ�
//=============================================================================
void TelopDrawer::SetVertexBG(float percentage)
{
	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(0, position.y - size.y*percentage, position.z);
	vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, position.y - size.y*percentage, position.z);
	vertexWk[2].vtx = D3DXVECTOR3(0, position.y + size.y*percentage, position.z);
	vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, position.y + size.y*percentage, position.z);
}

//=============================================================================
// �w�i���J������
//=============================================================================
void TelopDrawer::OpenBG(void)
{
	bgEasingStart = 0.0f;
	bgEasingGoal = 1.0f;

	percentage = Easing::EaseValue(GetCountObject(bgCloseOpenDuration), bgEasingStart, bgEasingGoal, InOutCubic);

	if (percentage >= bgEasingGoal)
	{
		isBG_Openinig = false;
		percentage = 1.0f;
		countFrame = 0;
	}
}

//=============================================================================
// �w�i����鏈��
//=============================================================================
void TelopDrawer::CloseBG(void)
{
	bgEasingStart = 1.0f;
	bgEasingGoal = 0.0f;

	percentage = Easing::EaseValue(GetCountObject(bgCloseOpenDuration), bgEasingStart, bgEasingGoal, InOutCubic);

	if (percentage <= bgEasingGoal)
	{
		isBG_Closing = false;
		percentage = 0.0f;
		countFrame = 0;
	}
}

//=============================================================================
// �I�u�W�F�N�g�J�E���g�擾����
//=============================================================================
float TelopDrawer::GetCountObject(float duration)
{
	countFrame++;
	float t = (float)countFrame / duration;

	return t;
}

//=============================================================================
// �w�i�A�j���[�V�����Đ�����
//=============================================================================
void TelopDrawer::PlayBG(void)
{
	if (isBG_Openinig) 
	{
		OpenBG();
	}

	if (isBG_Closing)
	{
		CloseBG();
	}
}

//=============================================================================
// �w�i���J�����Ƃ��J�n
//=============================================================================
void TelopDrawer::PlayBG_Open(void)
{
	isBG_Openinig = true;
}

//=============================================================================
// �w�i����邱�Ƃ��J�n
//=============================================================================
void TelopDrawer::PlayBG_Close(void)
{
	isBG_Closing = true;
}
