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
	static�����o
	***************************************/
	const float AlongActor::RangePositionOffset = 1.5f;
	const float AlongActor::MinScale = 0.9f;
	const float AlongActor::MaxScale = 1.2f;

	/**************************************
	�R���X�g���N�^
	***************************************/
	AlongActor::AlongActor()
	{
		mesh = new MeshContainer();
		ResourceManager::Instance()->GetMesh("AlongCity", mesh);
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
		float scale = Math::RandomRange(MinScale, MaxScale);
		Tween::Scale(*this, Vector3::Zero, Vector3::One * scale, 15, InCubic);
	}

	/**************************************
	���W�ݒ菈��
	***************************************/
	void AlongActor::SetPosition(const D3DXVECTOR3 & position)
	{
		float offsetX = Math::RandomRange(-RangePositionOffset, RangePositionOffset);
		float offsetY = Math::RandomRange(-RangePositionOffset, RangePositionOffset);
		float offsetZ = Math::RandomRange(-RangePositionOffset, RangePositionOffset);

		transform->SetPosition(position + D3DXVECTOR3(offsetX, offsetY, offsetZ));
	}
}