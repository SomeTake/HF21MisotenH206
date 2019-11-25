//=====================================
//
// �K�C�h�r���A�[�o�b�N�O���E���h[GuideViewerBG.cpp]
// �@�\�F�K�C�h�r���A�[�̔w�i
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GuideViewerBG.h"
#include "../../../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
GuideViewerBG::GuideViewerBG()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("GuideViewerBG", polygon);

	transform->Rotate(0.0f, 0.0f, 0.0f);
	transform->SetPosition(D3DXVECTOR3(0.0f, 50.0f, 50.0f));
	transform->SetScale(Vector3::One);
}

//=====================================
// �f�X�g���N�^
//=====================================
GuideViewerBG::~GuideViewerBG()
{
	SAFE_DELETE(polygon);
}

//=====================================
// �X�V
//=====================================
void GuideViewerBG::Update()
{

}

//=====================================
// �`��
//=====================================
void GuideViewerBG::Draw()
{
	polygon->Draw(transform->GetMatrix());
}
