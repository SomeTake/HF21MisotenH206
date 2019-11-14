//=============================================================================
//
// �A�ŃQ�[���Q�[�W�r���A�[���� [BeatGaugeViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "BeatGaugeViewer.h"

#ifdef _DEBUG

#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"

#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BeatGaugeViewer::BeatGaugeViewer()
{
	//�o�[
	bar = new BaseViewerDrawer();
	bar->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatGaugeViewer/Gauge.png");
	bar->size = D3DXVECTOR3(1600.0f, 120.0f, 0.0f);
	bar->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bar->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/3*2.40f, 0.0f);
	bar->MakeVertex();
	bar->SetTexture(1, 2, 1);

	//�t���[��
	frame = new BaseViewerDrawer();
	frame->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatGaugeViewer/Gauge.png");
	frame->size = D3DXVECTOR3(1600.0f, 120.0f, 0.0f);
	frame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frame->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/3*2.40f, 0.0f);
	frame->MakeVertex();
	frame->SetTexture(1, 2, 2);

	gaugePer = 1.0f;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BeatGaugeViewer::~BeatGaugeViewer()
{
	SAFE_DELETE(bar);
	SAFE_DELETE(frame);
}

//=============================================================================
// �X�V����
//=============================================================================
void BeatGaugeViewer::Update()
{
	if (Keyboard::GetTrigger(DIK_1))
	{
		gaugePer -= 0.10f;
	}

	if (Keyboard::GetTrigger(DIK_2))
	{
		gaugePer += 0.10f;
	}

	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�U��
	Shake();
}

//=============================================================================
// �`�揈��
//=============================================================================
void BeatGaugeViewer::Draw(void)
{
	////�Đ����Ȃ�`��
	//if (!isPlaying) return;

	//�o�[���ɕ`��
	DrawBar();

	//�t���[��
	frame->Draw();
}

//=============================================================================
// �U������
//=============================================================================
void BeatGaugeViewer::Shake()
{
}

//=============================================================================
// �Q�[�W�o�[�`�揈��
//=============================================================================
void BeatGaugeViewer::DrawBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	bar->vertexWk[0].vtx = bar->position + D3DXVECTOR3(-bar->size.x / 2, -bar->size.y / 2, 0.0f);
	bar->vertexWk[1].vtx = bar->position + D3DXVECTOR3(-bar->size.x/2 + (bar->size.x*gaugePer), -bar->size.y / 2, 0.0f);
	bar->vertexWk[2].vtx = bar->position + D3DXVECTOR3(-bar->size.x / 2, bar->size.y / 2, 0.0f);
	bar->vertexWk[3].vtx = bar->position + D3DXVECTOR3(-bar->size.x/2 + (bar->size.x*gaugePer), bar->size.y / 2, 0.0f);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, bar->texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bar->vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �Q�[�W�Z�b�g����
//=============================================================================
void BeatGaugeViewer::Set(float percent)
{
	//�Q�[�W�������Z�b�g
	gaugePer = percent;

	//�Đ���Ԃɂ���
	isPlaying = true;
}
