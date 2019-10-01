//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.cpp]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PlaceActor.h"

//=====================================
// �R���X�g���N�^
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos)
{
	// ���b�V���R���e�i�̍쐬
	mesh = MeshContainer::Create();

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(pos);
	SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// �X�V
//=====================================
void PlaceActor::Update()
{
	this->PlayAnimation(animType);
}

//=====================================
// �`��
//=====================================
void PlaceActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y����]
//=====================================
void PlaceActor::Rotate(float y)
{
	D3DXQUATERNION rot = transform->GetRotation();
	transform->SetRotation(D3DXQUATERNION(rot.x, rot.y + (FLOAT)y, rot.z, rot.w));
}

//=====================================
// �A�j���[�V�����Đ�
//=====================================
void PlaceActor::PlayAnimation(int AnimType)
{
	//switch (AnimType)
	//{
	//default:
	//	break;
	//}
}
