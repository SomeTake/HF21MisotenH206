//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.cpp]
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
	container->Create();
	container->Load("data/MODEL/transform.x");
	//ResourceManager::Instance()->GetMesh("tag", container);

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(pos);
	SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
PlaceActor::~PlaceActor()
{
	container->Release();
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
	container->Draw();
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
