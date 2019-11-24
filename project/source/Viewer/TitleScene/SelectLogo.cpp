//=====================================
//
// �Z���N�g���S[SelectLogo.cpp]
// �@�\�F�Z���N�g���S
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "SelectLogo.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
SelectLogo::SelectLogo()
{
	polygon = new BoardPolygon();
}

//=====================================
// �f�X�g���N�^
//=====================================
SelectLogo::~SelectLogo()
{
	SAFE_DELETE(polygon);
}

//=====================================
// �X�V
//=====================================
void SelectLogo::Update()
{
}

//=====================================
// �`��
//=====================================
void SelectLogo::Draw()
{
	polygon->Draw(transform->GetMatrix());
}

//=====================================
// ���\�[�X�ǂݍ���
//=====================================
void SelectLogo::LoadResource(const char * tag)
{
	ResourceManager::Instance()->GetPolygon(tag, polygon);
}

//=====================================
// ���W�Z�b�g
//=====================================
void SelectLogo::SetPosition(const D3DXVECTOR3 & pos)
{
	transform->SetPosition(pos);
}

//=====================================
// �������Z�b�g
//=====================================
void SelectLogo::SetTexDiv(const D3DXVECTOR2& div)
{
	polygon->SetTexDiv(div);
}

//=====================================
// �e�N�X�`���̕ύX
//=====================================
void SelectLogo::SetTextureIndex(int index)
{
	polygon->SetTextureIndex(index);
}
