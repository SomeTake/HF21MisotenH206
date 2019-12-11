//=====================================
//
// シティアクター[CityActor.cpp]
// 機能：都市（国、星）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CityActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MophingMeshContainer.h"

#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"

//=====================================
// コンストラクタ
//=====================================
CityActor::CityActor()
	: PlaceActor(),
	useMorphing(false)
{
	type = Field::Model::Town;

	morphingMesh = new MorphingMeshContainer();
}

//=====================================
// デストラクタ
//=====================================
CityActor::~CityActor()
{
	SAFE_DELETE(morphingMesh);
}

//=====================================
// 初期化処理
//=====================================
void CityActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel)
{
	using Field::Actor::ActorLoader;
	if (currentLevel == Field::FieldLevel::City)
	{
		for (int i = 0; i < 3; i++)
		{
			ResourceManager::Instance()->GetMesh(ActorLoader::CityTownTag[i].c_str(), morphingMesh);
			morphingMesh->RegisterVertex(i);
		}
		morphingMesh->SetCurrent(0);
		morphingMesh->SetNext(1);
		useMorphing = true;
	}
	else if (currentLevel == Field::FieldLevel::World)
	{
		for (int i = 0; i < 3; i++)
		{
			ResourceManager::Instance()->GetMesh(ActorLoader::WorldTownTag[i].c_str(), morphingMesh);
			morphingMesh->RegisterVertex(i);
		}
		morphingMesh->SetCurrent(0);
		morphingMesh->SetNext(1);
		useMorphing = true;
	}
	else
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::CityTag[currentLevel].c_str(), mesh);
		useMorphing = false;
	}


	PlaceActor::Init(pos, currentLevel);
}

//=====================================
// 終了処理
//=====================================
void CityActor::Uninit()
{
	morphingMesh->Reset();

	PlaceActor::Uninit();
}

//=====================================
// 更新処理
//=====================================
void CityActor::Update()
{
	t = Math::WrapAround(-0.5f, 1.5f, t + 0.02f);
	PlaceActor::Update();
}

//=====================================
// 描画処理
//=====================================
void CityActor::Draw()
{
	if (useMorphing)
	{
		morphingMesh->SetChange(t);
		morphingMesh->Draw(transform->GetMatrix());
	}
	else
	{
		PlaceActor::Draw();
	}
}
