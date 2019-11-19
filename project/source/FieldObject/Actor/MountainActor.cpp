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
#include "../../Field/Object/WaterHeightController.h"
#include "../../Effect/WorldParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"

//=====================================
// �R���X�g���N�^
//=====================================
MountainActor::MountainActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater)
	: PlaceActor(pos, currentLevel),
	effect(nullptr),
	speedWhirl(Math::RandomRange(0.02f, 0.05f)),
	emitter(nullptr)
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
		emitter = WorldParticleManager::Instance()->Generate(WorldParticle::WhirlPoolBubble, transform->GetPosition());
	}

	type = Field::Model::Mountain;
}

//=====================================
// �f�X�g���N�^
//=====================================
MountainActor::~MountainActor()
{
	SAFE_DELETE(effect);

	if (emitter != nullptr)
	{
		emitter->SetActive(false);
	}
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

	if (emitter != nullptr)
	{
		D3DXVECTOR3 position = emitter->GetPosition();
		position.y = WaterHeightController::GetHeight();
		emitter->SetPosition(position);
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
		//�����𐅖ʂɍ��킹��
		D3DXVECTOR3 position = transform->GetPosition();
		position.y = WaterHeightController::GetHeight() + 0.01f;
		transform->SetPosition(position);

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
