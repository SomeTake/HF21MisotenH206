//=====================================
//
// クロスジャンクションアクター[CrossJunctionActor.cpp]
// 機能：十字路3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CrossJunctionActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"

//=====================================
// コンストラクタ
//=====================================
CrossJunctionActor::CrossJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::CrossTag[currentLevel].c_str(), mesh);

	type = Field::Model::Junction;
}

//=====================================
// デストラクタ（メッシュの開放は基底クラスで）
//=====================================
CrossJunctionActor::~CrossJunctionActor()
{
}
