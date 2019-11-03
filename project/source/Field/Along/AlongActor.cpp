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
	const float AlongActor::RangePositionOffset = 2.0f;

	const float AlongActor::MinScale = 0.75f;
	const float AlongActor::MaxScale = 1.25f;
	const float AlongActor::MinScaleY = 1.0f;
	const float AlongActor::MaxScaleY = 1.5f;

	const D3DXCOLOR AlongActor::MaterialColor[] = {
		{ 1.0f, 0.4f, 0.4f, 1.0f },
		{ 0.4f, 0.4f, 1.0f, 1.0f },
		{ 1.0f, 0.9f, 0.6f, 1.0f }
	};

	/**************************************
	�R���X�g���N�^
	***************************************/
	AlongActor::AlongActor()
	{
		mesh = new MeshContainer();
		ResourceManager::Instance()->GetMesh("AlongCity", mesh);

		int colorIndex = Math::RandomRange(0, 3);
		mesh->SetMaterialColor(MaterialColor[colorIndex], 1);
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
		float scaleY = Math::RandomRange(MinScaleY, MaxScaleY);

		Tween::Scale(*this, Vector3::Zero, { scale, scaleY, scale }, 15, InCubic);

		int rotation = Math::RandomRange(0, 8);
		transform->Rotate(rotation * 45.0f, Vector3::Up);
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