//=====================================
//
//AlongActor.cpp
//�@�\:�������̃A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "AlongActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../../Framework/Tween/Tween.h"

namespace Field::Along
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	AlongActor::AlongActor()
	{
		mesh = new MeshContainer();
		ResourceManager::Instance()->GetMesh("AlongActor", mesh);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	AlongActor::~AlongActor()
	{
		SAFE_DELETE(mesh);
	}

	/**************************************
	�X�V����
	***************************************/
	void AlongActor::Update()
	{
	}

	/**************************************
	�`�揈��
	***************************************/
	void AlongActor::Draw(const D3DXMATRIX& parent)
	{
		transform->SetWorld(&parent);
		mesh->Draw();
	}

	/**************************************
	�A�j���[�V�����Đ�
	***************************************/
	void AlongActor::PlayAnimation()
	{
		Tween::Scale(*this, Vector3::Zero, Vector3::One, 15, InCubic);
	}
}