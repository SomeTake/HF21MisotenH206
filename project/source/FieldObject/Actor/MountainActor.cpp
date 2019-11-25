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
#include "../../Effect/SpaceParticleManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
MountainActor::MountainActor()
	: PlaceActor(),
	effect(nullptr),
	speedWhirl(0.0f),
	emitter(nullptr),
	level(Field::FieldLevel::City),
	onWater(false)
{
	effect = new Field::Actor::WhirlPoolEffect();

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
		emitter = nullptr;
	}
}

//=====================================
// ����������
//=====================================
void MountainActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel, bool onWater)
{
	PlaceActor::Init(pos, currentLevel);

	this->level = currentLevel;
	this->onWater = onWater;

	using Field::Actor::ActorLoader;

	if (!onWater)
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::MountainTag[currentLevel].c_str(), mesh);

		if (currentLevel == Field::FieldLevel::Space)
		{
			emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::Blackhole, transform->GetPosition());
			speedWhirl = Math::RandomRange(0.005f, 0.01f);
		}
	}
	else
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::WhirlPoolTag.c_str(), mesh);

		emitter = WorldParticleManager::Instance()->Generate(WorldParticle::WhirlPoolBubble, transform->GetPosition());
		speedWhirl = Math::RandomRange(0.02f, 0.05f);
	}
}

//=====================================
// �I������
//=====================================
void MountainActor::Uninit()
{
	if (emitter != nullptr)
	{
		emitter->SetActive(false);
		emitter = nullptr;
	}
}

//=====================================
// �X�V����
//=====================================
void MountainActor::Update()
{
	//���� or �F���̏ꍇ�͉�]������
	if (onWater || level == Field::FieldLevel::Space)
	{
		cntWhirl += speedWhirl;
		effect->SetTime(cntWhirl);
	}

	//����Ȃ�Q���G�~�b�^�𐅖ʂɂ��킹��
	if (onWater)
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
	if (onWater)
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
