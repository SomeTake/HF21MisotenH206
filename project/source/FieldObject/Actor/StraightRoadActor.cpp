//=====================================
//
// �X�g���[�g���[�h�A�N�^�[[StraightRoadActor.cpp]
// �@�\�F�܂������ȓ��p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "StraightRoadActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"

//=====================================
// �R���X�g���N�^
//=====================================
StraightRoadActor::StraightRoadActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel),
	emitter(nullptr)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::StraightTag[currentLevel].c_str(), mesh);

	type = Field::Model::Road;

	if (currentLevel == Field::FieldLevel::Space)
	{
		emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);
	}
}

//=====================================
// �f�X�g���N�^
//=====================================
StraightRoadActor::~StraightRoadActor()
{
	if (emitter != nullptr)
		emitter->SetActive(false);
}

//=====================================
// ��]����
//=====================================
void StraightRoadActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	if (emitter != nullptr)
	{
		D3DXVECTOR3 euler = transform->GetEulerAngle();
		emitter->SetRotatition(euler);
	}
}
