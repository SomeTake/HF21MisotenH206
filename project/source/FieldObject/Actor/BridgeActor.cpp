//=====================================
//
// �u���b�W�A�N�^�[[BridgeActor.cpp]
// �@�\�F���i���[�v�z�[���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "BridgeActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Shader/RiverEffect.h"

//=====================================
// �R���X�g���N�^
//=====================================
BridgeActor::BridgeActor()
	: PlaceActor(),
	effect(nullptr),
	uv(0.0f, 0.0f),
	level(Field::FieldLevel::City)
{
	effect = new Field::Actor::RiverEffect();

	type = Field::Model::Bridge;
}

//=====================================
// �f�X�g���N�^
//=====================================
BridgeActor::~BridgeActor()
{
	SAFE_DELETE(effect);
}

//=====================================
// ����������
//=====================================
void BridgeActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::BridgeTag[currentLevel].c_str(), mesh);
	
	level = currentLevel;

	PlaceActor::Init(pos, currentLevel);
}

//=====================================
// �X�V����
//=====================================
void BridgeActor::Update()
{
	PlaceActor::Update();

	if (level == Field::FieldLevel::Space)
	{
		uv.y += 0.005f;
		effect->SetUV(uv);
	}
}

//=====================================
// �`�揈��
//=====================================
void BridgeActor::Draw()
{
	if (level != Field::FieldLevel::Space)
	{
		PlaceActor::Draw();
	}
	else
	{
		if (!this->IsActive())
			return;

		if (!onCamera)
			return;

		effect->Begin();
		effect->BeginPass(0);

		effect->SetWorld(*transform);
		mesh->Draw(*effect);

		effect->EndPass();
		effect->End();
	}
}