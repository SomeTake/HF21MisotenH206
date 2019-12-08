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
#include "../../Effect/SpaceParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// �R���X�g���N�^
//=====================================
CurveRoadActor::CurveRoadActor()
	: PlaceActor(),
	onWater(false)
{

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
// ����������
//=====================================
void CurveRoadActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel, bool onWater)
{
	PlaceActor::Init(pos, currentLevel);

	this->onWater = onWater;

	using Field::Actor::ActorLoader;
	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::CurveTag[currentLevel].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterCurve.c_str(), mesh);

	type = Field::Model::Road;

	if (currentLevel == Field::FieldLevel::Space)
	{
		emitterContainer.resize(2, nullptr);
		D3DXVECTOR3 euler = transform->GetEulerAngle();

		for (auto&& emitter : emitterContainer)
		{
			//�G�~�b�^�[�Z�b�g
			emitter = SpaceParticleManager::Instance()->Generate(SpaceParticle::StarRoad, *transform);

			if (emitter != nullptr)
				emitter->SetRotatition(euler);

			euler.y -= 90.0f;
		}
	}
}

//=====================================
// �I������
//=====================================
void CurveRoadActor::Uninit()
{
	PlaceActor::Uninit();
	for (auto&& emitter : emitterContainer)
	{
		if (emitter != nullptr)
			emitter->SetActive(false);
	}
	emitterContainer.clear();
}

//=====================================
// �`�揈��
//=====================================
void CurveRoadActor::Draw()
{
	//����Ȃ琅�ʂɍ��������킹��
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

//=====================================
// �C�㔻��ݒ�
//=====================================
void CurveRoadActor::OnSea(bool state)
{
	this->onWater = state;

	using Field::Actor::ActorLoader;
	if (!onWater)
		ResourceManager::Instance()->GetMesh(ActorLoader::CurveTag[Field::FieldLevel::World].c_str(), mesh);
	else
		ResourceManager::Instance()->GetMesh(ActorLoader::WaterCurve.c_str(), mesh);
}
