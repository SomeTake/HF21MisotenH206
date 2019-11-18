//=====================================
//
// �N���X�W�����N�V�����A�N�^�[[CrossJunctionActor.cpp]
// �@�\�F�\���H3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CrossJunctionActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// �R���X�g���N�^
//=====================================
CrossJunctionActor::CrossJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater)
	: PlaceActor(pos, currentLevel),
	onWater(onWater)
{
	using Field::Actor::ActorLoader;
	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::CrossTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterCross.c_str(), mesh);


	type = Field::Model::Junction;

	if (currentLevel == Field::FieldLevel::Space)
	{
		D3DXVECTOR3 euler = transform->GetEulerAngle();
		emitterContainer.resize(4, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = GameParticleManager::Instance()->Generate(GameParticle::StarRoad, *transform);
			if (emitter != nullptr)
			{
				emitter->SetRotatition(euler);
			}

			euler.y += 90.0f;
		}
	}
}

//=====================================
// �f�X�g���N�^�i���b�V���̊J���͊��N���X�Łj
//=====================================
CrossJunctionActor::~CrossJunctionActor()
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
void CrossJunctionActor::Draw()
{
	//���ʂȂ獂�������킹��
	if (onWater)
	{
		D3DXVECTOR3 position = transform->GetPosition();
		position.y = WaterHeightController::GetHeight();
		transform->SetPosition(position);
	}

	PlaceActor::Draw();
}

//=====================================
// ��]����
//=====================================
void CrossJunctionActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	D3DXVECTOR3 euler = transform->GetEulerAngle();
	for (auto&& emitter : emitterContainer)
	{
		if (emitter == nullptr)
			continue;

		emitter->SetRotatition(euler);
		euler.y += 90.0f;
	}
}
