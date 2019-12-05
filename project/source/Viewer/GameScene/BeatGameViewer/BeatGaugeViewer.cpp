//=============================================================================
//
// �A�ŃQ�[���Q�[�W�r���A�[���� [BeatGaugeViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "BeatGaugeViewer.h"

#include "../../../../main.h"
#include "../../Framework/BaseViewer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BeatGaugeViewer::BeatGaugeViewer()
{
	//�o�[
	bar = new BaseViewerDrawer();
	bar->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatGaugeViewer/Gauge01.png");
	bar->size = D3DXVECTOR3(1300.0f, 120.0f, 0.0f);
	bar->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bar->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/3*2.40f, 0.0f);
	bar->MakeVertex();
	bar->SetTexture(1, 2, 1);

	//�t���[��
	frame = new BaseViewerDrawer();
	frame->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatGaugeViewer/Gauge01.png");
	frame->size = D3DXVECTOR3(1600.0f, 120.0f, 0.0f);
	frame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frame->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/3*2.40f, 0.0f);
	frame->MakeVertex();
	frame->SetTexture(1, 2, 2);

	//�A�j���[�V����
	anim = new ViewerAnimater();
	std::vector<std::function<void()>> vec = {
	[=] {
		//�U��
		anim->Shake(*frame, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT / 3 * 2.40f), 2.0f);
	} };
	anim->SetAnimBehavior(vec);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BeatGaugeViewer::~BeatGaugeViewer()
{
	SAFE_DELETE(bar);
	SAFE_DELETE(frame);
	SAFE_DELETE(anim);
}

//=============================================================================
// �X�V����
//=============================================================================
void BeatGaugeViewer::Update()
{
	//�Q�[�W�p�[�Z���g���������Ȃ�����U��
	if (isCurrentSmallerLast(gaugePer)) isPlaying = true;
	if (!isPlaying) return;
	anim->PlayAnim([=]
	{
		anim->SetPlayFinished(isPlaying);
	});
}

//=============================================================================
// �`�揈��
//=============================================================================
void BeatGaugeViewer::Draw(void)
{
	//�o�[���ɕ`��
	DrawBar();

	//�t���[��
	frame->Draw();
}

//=============================================================================
// �Q�[�W�o�[�`�揈��
//=============================================================================
void BeatGaugeViewer::DrawBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	bar->vertexWk[0].vtx = bar->position + D3DXVECTOR3(-bar->size.x / 2, -bar->size.y / 2, 0.0f);
	bar->vertexWk[1].vtx = bar->position + D3DXVECTOR3(-bar->size.x / 2 + (bar->size.x*gaugePer), -bar->size.y / 2, 0.0f);
	bar->vertexWk[2].vtx = bar->position + D3DXVECTOR3(-bar->size.x / 2, bar->size.y / 2, 0.0f);
	bar->vertexWk[3].vtx = bar->position + D3DXVECTOR3(-bar->size.x / 2 + (bar->size.x*gaugePer), bar->size.y / 2, 0.0f);

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
}
