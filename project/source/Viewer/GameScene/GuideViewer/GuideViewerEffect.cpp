//=====================================
//
// �K�C�h�r���A�[�G�t�F�N�g[GuideViewerEffect.h]
// �@�\�F�K�C�h�r���A�[�̃G�t�F�N�g
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GuideViewerEffect.h"
#include "GuideViewer.h"

//=====================================
// �R���X�g���N�^
//=====================================
GuideViewerEffect::GuideViewerEffect()
{
	polygon = new Polygon2D();
	polygon->LoadTexture("data/TEXTURE/Viewer/GameViewer/GuideViewer/White-Effect.png");
	polygon->SetSize(GuideViewer::SubScreenSize.x, GuideViewer::SubScreenSize.y);
	polygon->SetActive(true);
	polygon->SetPosition(Vector3::Zero);
	polygon->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	polygon->SetColor(D3DXCOLOR(0.615f, 0.800f, 1.0f, 0.800f));
}

//=====================================
// �f�X�g���N�^
//=====================================
GuideViewerEffect::~GuideViewerEffect()
{
	SAFE_DELETE(polygon);
}

//=====================================
// �X�V
//=====================================
void GuideViewerEffect::Update()
{
}

//=====================================
// �`��
//=====================================
void GuideViewerEffect::Draw()
{
	polygon->Draw();
}
