//=============================================================================
//
// �X�g�b�N�r���A�[���� [BanIcon.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../main.h"
#include "BanIcon.h"
#include "../../../Framework/Math/Easing.h"


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
const int DefaultDebuffFrame = 300;


//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BanIcon::BanIcon() :
	RemainFrame(DefaultDebuffFrame),
	IsPlaying(false)
{
	Icon = new BaseViewerDrawer();
	Icon->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/BanStock.png");
	Icon->size = D3DXVECTOR3(90.0f, 90.0f, 0.0f);
	Icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Icon->position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 360.0f, SCREEN_HEIGHT / 2, 0.0f);
	Icon->SetColor(SET_COLOR_NOT_COLORED);
	Icon->MakeVertex();

	Icon1 = new BaseViewerDrawer();
	Icon1->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/BanStock.png");
	Icon1->size = D3DXVECTOR3(90.0f, 90.0f, 0.0f);
	Icon1->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Icon1->position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	Icon1->SetColor(SET_COLOR_NOT_COLORED);
	Icon1->MakeVertex();

	Icon2 = new BaseViewerDrawer();
	Icon2->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/BanStock.png");
	Icon2->size = D3DXVECTOR3(90.0f, 90.0f, 0.0f);
	Icon2->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Icon2->position = D3DXVECTOR3(SCREEN_WIDTH / 2 + 360.0f, SCREEN_HEIGHT / 2, 0.0f);
	Icon2->SetColor(SET_COLOR_NOT_COLORED);
	Icon2->MakeVertex();

	Icon2_White = new BaseViewerDrawer();
	Icon2_White->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/BanStock_White.png");
	Icon2_White->size = D3DXVECTOR3(90.0f, 90.0f, 0.0f);
	Icon2_White->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Icon2_White->position = D3DXVECTOR3(SCREEN_WIDTH / 2 + 360.0f, SCREEN_HEIGHT / 2, 0.0f);
	Icon2_White->SetColor(SET_COLOR_NOT_COLORED);
	Icon2_White->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BanIcon::~BanIcon()
{
	SAFE_DELETE(Icon);
	SAFE_DELETE(Icon1);
	SAFE_DELETE(Icon2);
	SAFE_DELETE(Icon2_White);
}

//=============================================================================
// ������
//=============================================================================
void BanIcon::Init(void)
{
	this->RemainFrame = DefaultDebuffFrame;
	this->IsPlaying = true;
}

//=============================================================================
// �X�V����
//=============================================================================
void BanIcon::Update(void)
{
	if (!IsPlaying)
		return;

	//�A�j���[�V����
	Animate();
}

//=============================================================================
// �`�揈��
//=============================================================================
void BanIcon::Draw(void)
{
	if (!IsPlaying)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Device->SetRenderState(D3DRS_ALPHAREF, 0);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	Icon->Draw();
	Icon1->Draw();
	Icon2->Draw();
	Icon2_White->Draw();

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �A�j���[�V��������
//=============================================================================
void BanIcon::Animate(void)
{
	RemainFrame--;

	float RemainTimePercent = (float)RemainFrame / (float)DefaultDebuffFrame;

	Icon->SetAlpha(RemainTimePercent);

	float Percent = Easing::EaseValue((1 - RemainTimePercent), 1.0f, -1.0f, EaseType::Linear);
	SetVertex(Percent);
	SetTexture(RemainTimePercent);

	if (RemainFrame <= 0)
	{
		IsPlaying = false;
	}
}

//=============================================================================
// ���_���W�ݒu
//=============================================================================
void BanIcon::SetVertex(float Percent)
{
	Icon1->vertexWk[0].vtx = Icon1->position + D3DXVECTOR3(-Icon1->size.x, -Icon1->size.y * Percent, 0.0f);
	Icon1->vertexWk[1].vtx = Icon1->position + D3DXVECTOR3(Icon1->size.x, -Icon1->size.y * Percent, 0.0f);
	Icon1->vertexWk[2].vtx = Icon1->position + D3DXVECTOR3(-Icon1->size.x, Icon1->size.y, 0.0f);
	Icon1->vertexWk[3].vtx = Icon1->position + D3DXVECTOR3(Icon1->size.x, Icon1->size.y, 0.0f);

	Icon2->vertexWk[0].vtx = Icon2->position + D3DXVECTOR3(-Icon2->size.x, -Icon2->size.y * Percent, 0.0f);
	Icon2->vertexWk[1].vtx = Icon2->position + D3DXVECTOR3(Icon2->size.x, -Icon2->size.y * Percent, 0.0f);
	Icon2->vertexWk[2].vtx = Icon2->position + D3DXVECTOR3(-Icon2->size.x, Icon2->size.y, 0.0f);
	Icon2->vertexWk[3].vtx = Icon2->position + D3DXVECTOR3(Icon2->size.x, Icon2->size.y, 0.0f);

	Icon2_White->vertexWk[0].vtx = Icon2_White->position + D3DXVECTOR3(-Icon2_White->size.x, -Icon2_White->size.y, 0.0f);
	Icon2_White->vertexWk[1].vtx = Icon2_White->position + D3DXVECTOR3(Icon2_White->size.x, -Icon2_White->size.y, 0.0f);
	Icon2_White->vertexWk[2].vtx = Icon2_White->position + D3DXVECTOR3(-Icon2_White->size.x, Icon2_White->size.y * -Percent, 0.0f);
	Icon2_White->vertexWk[3].vtx = Icon2_White->position + D3DXVECTOR3(Icon2_White->size.x, Icon2_White->size.y * -Percent, 0.0f);
}

//=============================================================================
// ���_���W�ݒu
//=============================================================================
void BanIcon::SetTexture(float Percent)
{
	Icon1->vertexWk[0].tex = D3DXVECTOR2(0.0f, (1 - Percent));
	Icon1->vertexWk[1].tex = D3DXVECTOR2(1.0f, (1 - Percent));
	Icon1->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Icon1->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	Icon2->vertexWk[0].tex = D3DXVECTOR2(0.0f, (1 - Percent));
	Icon2->vertexWk[1].tex = D3DXVECTOR2(1.0f, (1 - Percent));
	Icon2->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Icon2->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	Icon2_White->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Icon2_White->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Icon2_White->vertexWk[2].tex = D3DXVECTOR2(0.0f, (1 - Percent));
	Icon2_White->vertexWk[3].tex = D3DXVECTOR2(1.0f, (1 - Percent));
}



