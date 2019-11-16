//=====================================
//
// �J�[�u���[�h�A�N�^�[[CurveRoadActor.cpp]
// �@�\�F�J�[�u�p��3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CurveRoadActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"

//=====================================
// �R���X�g���N�^
//=====================================
CurveRoadActor::CurveRoadActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::CurveTag[currentLevel].c_str(), mesh);

	type = Field::Model::Road;

	if (currentLevel == Field::FieldLevel::Space)
	{
		emitterContainer.resize(2, nullptr);
		D3DXVECTOR3 euler = transform->GetEulerAngle();

		for (auto&& emitter : emitterContainer)
		{
			//�G�~�b�^�[�Z�b�g
			emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);

			if (emitter != nullptr)
				emitter->SetRotatition(euler);

			euler.y -= 90.0f;
		}
	}

}

//=====================================
// �f�X�g���N�^
//=====================================
CurveRoadActor::~CurveRoadActor()
{
	for (auto&& emitter : emitterContainer)
	{
		if (emitter != nullptr)
			emitter->SetActive(false);
	}
}

//=====================================
// ��]����
//=====================================
void CurveRoadActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	D3DXVECTOR3 euler = transform->GetEulerAngle();
	for (auto&& emitter : emitterContainer)
	{
		if (emitter != nullptr)
		{
			emitter->SetRotatition(euler);
			euler.y -= 90.0f;
		}
	}
}
