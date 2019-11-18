//=====================================
//
// �}�E���e���A�N�^�[[MountainActor.cpp]
// �@�\�F�R�i�Q���A�u���b�N�z�[���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "MountainActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Shader/WhirlPoolEffect.h"

//=====================================
// �R���X�g���N�^
//=====================================
MountainActor::MountainActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater)
	: PlaceActor(pos, currentLevel),
	effect(nullptr),
	speedWhirl(Math::RandomRange(0.01f, 0.05f))
{
	using Field::Actor::ActorLoader;
	if (!onWater)
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::MountainTag[currentLevel].c_str(), mesh);
	}
	else
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::WhirlPoolTag.c_str(), mesh);

		effect = new Field::Actor::WhirlPoolEffect();
	}

	type = Field::Model::Mountain;
}

//=====================================
// �f�X�g���N�^
//=====================================
MountainActor::~MountainActor()
{
	SAFE_DELETE(effect);
}

//=====================================
// �X�V����
//=====================================
void MountainActor::Update()
{
	if (effect != nullptr)
	{
		cntWhirl += speedWhirl;
		effect->SetTime(cntWhirl);
	}

	PlaceActor::Update();
}

//=====================================
// �`�揈��
//=====================================
void MountainActor::Draw()
{
	if (effect != nullptr)
	{
		effect->SetWorld(*transform);
		effect->Begin();
		effect->BeginPass(0);

		mesh->Draw(*effect);

		effect->EndPass();
		effect->End();
	}
	else
	{
		transform->SetWorld();
		mesh->Draw();
	}
}
