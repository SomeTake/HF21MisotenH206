//=====================================
//
// �C���t�H�A�N�^�[[InfoActor.cpp]
// �@�\�F�t�B�[���h��ɏ���\�����邽�߂̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "InfoActor.h"
#include "../../../Framework/Camera/Camera.h"
#include "../../../Framework/Camera/ViewFrustum.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const float InfoActor::ActorSize = 5.0f;

//=====================================
// �R���X�g���N�^
//=====================================
InfoActor::InfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(Vector3::One);
	this->SetActive(true);

	// �r���[�A�̍쐬
	viewer = new Viewer3D(256, 256, D3DXVECTOR2(ActorSize, ActorSize));
	viewer->SetPosition(D3DXVECTOR3(pos));
}

//=====================================
// �f�X�g���N�^
//=====================================
InfoActor::~InfoActor()
{
	SAFE_DELETE(viewer);
}