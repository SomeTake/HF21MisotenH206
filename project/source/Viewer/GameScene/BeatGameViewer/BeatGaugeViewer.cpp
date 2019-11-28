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
	//�U������
	HandleShake();
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
// �U�����䏈��
//=============================================================================
void BeatGaugeViewer::HandleShake()
{
	//�Ƃ肠�����p�����[�^�̍��Ŏ���
	currentParam = gaugePer;

	if (currentParam < lastParam)
	{
		shouldShake = true;
	}

	lastParam = gaugePer;

	//�U��������ׂ��Ȃ���s
	if (shouldShake)
	{
		Shake();
	}
}

//=============================================================================
// �U������
//=============================================================================
void BeatGaugeViewer::Shake()
{
	//����U�������邩
	const int shakeNum = 400;
	//�ǂ̂��炢�̐U�ꕝ��
	const float shakeValue = 3.0f;
	//�ǂ̂��炢�̎��ԐU�������邩
	const float shakeTime = 2.0f;
	//�������W
	const float initPosX = SCREEN_CENTER_X;
	const float initPosY = SCREEN_HEIGHT / 3 * 2.40f;
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	const float easingStart = 0.0f;
	const float easingGoal = D3DX_PI * shakeNum;

	countFrame++;
	animTime = countFrame / shakeTime;

	radian = Easing::EaseValue(animTime, easingStart, easingGoal, OutCirc);

	frame->position.x = initPosX + shakeValue * sinf(radian);
	frame->position.y = initPosY + shakeValue * sinf(radian);

	if (radian >= easingGoal)
	{
		//���W��������
		frame->position.x = initPosX;
		frame->position.y = initPosY;

		radian = 0.0f;
		countFrame = 0;
		animTime = 0;
		shouldShake = false;
	}
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
}
