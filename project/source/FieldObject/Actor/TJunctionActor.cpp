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

//=====================================
// �R���X�g���N�^
//=====================================
TJunctionActor::TJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::TJunctionTag[currentLevel].c_str(), mesh);

	type = Field::Model::Junction;

	emitterContainer.resize(2, nullptr);

	D3DXVECTOR3 euler = transform->GetEulerAngle();
	euler.y += 90.0f;

	//�������̃G�~�b�^�[���Z�b�g
	BaseEmitter* emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);
	if (emitter != nullptr)
	{
		emitter->SetRotatition(euler);
		emitterContainer[0] = emitter;
	}

	//�������̃G�~�b�^�[���Z�b�g
	euler.y += 90.0f;
	emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);
	if (emitter != nullptr)
	{
		emitter->SetRotatition(euler);
		emitterContainer[1] = emitter;
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
