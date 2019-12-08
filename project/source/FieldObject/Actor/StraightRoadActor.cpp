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
StraightRoadActor::StraightRoadActor()
	: PlaceActor(),
	emitter(nullptr),
	onWater(onWater)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
StraightRoadActor::~StraightRoadActor()
{
	if (emitter != nullptr)
	{
		emitter->SetActive(false);
		emitter = nullptr;
	}
}

//=====================================
// ����������
//=====================================
void StraightRoadActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel, bool onWataer)
{
	PlaceActor::Init(pos, currentLevel);

	using Field::Actor::ActorLoader;

	this->onWater = onWataer;

	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::StraightTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterStraight.c_str(), mesh);

	if (currentLevel == Field::FieldLevel::Space)
	{
		emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::StarRoad, *transform);
	}
}

//=====================================
// �I������
//=====================================
void StraightRoadActor::Uninit()
{
	PlaceActor::Uninit();
	if (emitter != nullptr)
	{
		emitter->SetActive(false);
		emitter = nullptr;
	}
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

//=====================================
// �C�㔻��ݒ�
//=====================================
void StraightRoadActor::OnSea(bool state)
{
	using Field::Actor::ActorLoader;

	this->onWater = state;

	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::StraightTag[Field::FieldLevel::World].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterStraight.c_str(), mesh);
}
