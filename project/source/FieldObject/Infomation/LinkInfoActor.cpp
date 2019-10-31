#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& pos, const int& level):
	InfoActor(pos), linkLevel(level)
{
	// 3D�r���[���[�̍쐬
	viewer = new Viewer3D(30, 10, D3DXVECTOR2(9.0f, 3.0f));

	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;

}

//=====================================
// �f�X�g���N�^
//=====================================
LinkInfoActor::~LinkInfoActor()
{
}

//=====================================
// �X�V
//=====================================
void LinkInfoActor::Update()
{
}

//=====================================
// �`��
//=====================================
void LinkInfoActor::Draw()
{
	if (!this->IsActive())
		return;
}

// ���x���ύX���g�p
void LinkInfoActor::SetLevel(const int& nextLevel)
{
	linkLevel = nextLevel;
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
}
