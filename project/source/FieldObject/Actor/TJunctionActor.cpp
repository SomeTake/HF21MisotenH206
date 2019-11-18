//=====================================
//
// T�W�����N�V�����A�N�^�[[TJunctionActor.h]
// �@�\�FT���H3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "TJunctionActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// �R���X�g���N�^
//=====================================
TJunctionActor::TJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater)
	: PlaceActor(pos, currentLevel),
	onWater(onWater)
{
	using Field::Actor::ActorLoader;
	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::TJunctionTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterT.c_str(), mesh);

	type = Field::Model::Junction;

	emitterContainer.resize(3, nullptr);

	D3DXVECTOR3 euler = transform->GetEulerAngle();

	if (currentLevel == Field::FieldLevel::Space)
	{
		for (auto&& emitter : emitterContainer)
		{
			euler.y += 90.0f;

			emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);
			if(emitter != nullptr)
				emitter->SetRotatition(euler);
		}
	}
}

//=====================================
// �f�X�g���N�^
//=====================================
TJunctionActor::~TJunctionActor()
{
	for (auto&& emitter : emitterContainer)
	{
		if (emitter == nullptr)
			continue;

		emitter->SetActive(false);
	}
}

//=====================================
// �`�揈��
//=====================================
void TJunctionActor::Draw()
{
	//����Ȃ獂�������킹��
	if (onWater)
	{
		D3DXVECTOR3 position = transform->GetPosition();
		position.y = WaterHeightController::GetHeight();
		transform->SetPosition(position);
	}
}

//=====================================
// ��]����
//=====================================
void TJunctionActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	D3DXVECTOR3 euler = transform->GetEulerAngle();
	for (auto&& emitter : emitterContainer)
	{
		euler.y += 90.0f;

		if (emitter == nullptr)
			continue;

		emitter->SetRotatition(euler);
	}
}
