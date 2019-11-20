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
#include "../../Effect/SpaceParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// �R���X�g���N�^
//=====================================
StraightRoadActor::StraightRoadActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater)
	: PlaceActor(pos, currentLevel),
	emitter(nullptr),
	onWater(onWater)
{
	using Field::Actor::ActorLoader;

	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::StraightTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterStraight.c_str(), mesh);

	type = Field::Model::Road;

	if (currentLevel == Field::FieldLevel::Space)
	{
		emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::StarRoad, *transform);
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
// �`�揈��
//=====================================
void StraightRoadActor::Draw()
{
	//����Ȃ獂���𐅖ʂɍ��킹��
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
void StraightRoadActor::Rotate(float y)
{
	PlaceActor::Rotate(y);

	if (emitter != nullptr)
	{
		D3DXVECTOR3 euler = transform->GetEulerAngle();
		emitter->SetRotatition(euler);
	}
}
