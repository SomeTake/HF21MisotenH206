//=====================================
//
// マウンテンアクター[MountainActor.cpp]
// 機能：山（渦潮、ブラックホール）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "MountainActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../Shader/WhirlPoolEffect.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// コンストラクタ
//=====================================
MountainActor::MountainActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater)
	: PlaceActor(pos, currentLevel),
	effect(nullptr),
	speedWhirl(Math::RandomRange(0.03f, 0.08f))
{
	using Field::Actor::ActorLoader;
	if (!onWater)
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::MountainTag[currentLevel].c_str(), mesh);
	}
	else
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::WhirlPoolTag.c_str(), mesh);

		effect = new Field::Actor::WhirlPoolEffect();
	}

	type = Field::Model::Mountain;
}

//=====================================
// デストラクタ
//=====================================
MountainActor::~MountainActor()
{
	SAFE_DELETE(effect);
}

//=====================================
// 更新処理
//=====================================
void MountainActor::Update()
{
	if (effect != nullptr)
	{
		cntWhirl += speedWhirl;
		effect->SetTime(cntWhirl);
	}

	PlaceActor::Update();
}

//=====================================
// 描画処理
//=====================================
void MountainActor::Draw()
{
	if (effect != nullptr)
	{
		//高さを水面に合わせる
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
