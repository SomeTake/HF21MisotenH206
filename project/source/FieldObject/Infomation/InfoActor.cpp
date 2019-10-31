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
const D3DXVECTOR2 InfoActor::ViewerWorldSize = D3DXVECTOR2(5.0f, 5.0f);
const DWORD InfoActor::ViewerCanvasSize = 256;

//=====================================
// �R���X�g���N�^
//=====================================
InfoActor::InfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(Vector3::One);
	this->SetActive(true);

	// �r���[�A�̍쐬
	viewer = new Viewer3D(ViewerCanvasSize, ViewerCanvasSize, ViewerWorldSize);
	viewer->SetPosition(D3DXVECTOR3(pos));
}

//=====================================
// �f�X�g���N�^
//=====================================
InfoActor::~InfoActor()
{
	SAFE_DELETE(viewer);
}