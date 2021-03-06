//=====================================
//
//WorldBackGroundContainer.cpp
//機能:Worldレベルの背景コンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "WorldBackGroundContainer.h"
#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../FieldObject/Actor/RiverActor.h"
#include "../../FieldObject/Actor/NoneActor.h"
#include "../ActorLoader.h"

#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"
#include "../../../Framework/String/String.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Resource/ResourceManager.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	コンストラクタ
	***************************************/
	WorldBackGroundContainer::WorldBackGroundContainer()
	{
		//riverContainerを海として扱う
		const unsigned ReserveSizeSea = 10000;
		const unsigned ReserveSizeGround = 2000;

		riverContainer.reserve(ReserveSizeSea);
		groundContainer.reserve(ReserveSizeGround);
		seaMap.reserve(ReserveSizeSea);

		groundMesh = new InstancingMeshContainer(ReserveSizeGround);
		seaMesh = new InstancingMeshContainer(ReserveSizeSea);
	}

	/**************************************
	デストラクタ
	***************************************/
	WorldBackGroundContainer::~WorldBackGroundContainer()
	{
		SAFE_DELETE(groundMesh);
		SAFE_DELETE(seaMesh);
	}

	/**************************************
	更新処理
	***************************************/
	void WorldBackGroundContainer::Update()
	{
		for (auto&& sea : riverContainer)
		{
			sea->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void WorldBackGroundContainer::Draw()
	{
		//地面の描画
		groundMesh->Lock();
		for (auto&& ground : groundContainer)
		{
			bool res = groundMesh->EmbedTranform(ground->GetTransform());
			if (!res)
				break;
		}
		groundMesh->Unlock();

		groundMesh->Draw();

		//海の描画
		seaMesh->Lock();
		for (auto&& sea : riverContainer)
		{
			bool res = seaMesh->EmbedTranform(sea->GetTransform());
			if (!res)
				break;
		}
		seaMesh->Unlock();

		seaMesh->Draw();
	}

	/**************************************
	読み込み処理
	***************************************/
	void WorldBackGroundContainer::Load(int csvNo)
	{
		using Model::PlaceType;

		//CSVファイルを読み込み
		std::ifstream layerData(Const::FieldLayerFile[csvNo]);

		std::string layerLine;
		const char Delim = ',';		//区切り文字
		int x = 0;					//PlaceのX位置
		int z = 0;					//PlaceのZ位置

		//CSVの終わりまで読み込み続ける
		while (std::getline(layerData, layerLine))
		{
			//1行分読み込んだデータを区切り文字で分割する
			std::vector<std::string> subStrLayer;
			String::Split(subStrLayer, layerLine, Delim);

			x = 0;

			//分割したデータ毎にPlaceModelを作成
			for(auto&& layer : subStrLayer)
			{
				int type = std::stoi(layer);

				D3DXVECTOR3 position = Field::FieldPosition(x, z).ConvertToWorldPosition();
				PlaceActor *actor = nullptr;

				if (type == FieldLayer::Sea)
				{
					actor = ObjectPool::Instance()->Create<RiverActor>(position, FieldLevel::City);		//Cityと同じなのでとりあえず
					riverContainer.push_back(actor);

					//seaMapに追加
					seaMap.push_back(FieldPosition(x, z));
				}
				else
				{
					//真っ平らだと不自然なので高さに少し凹凸をつける
					position.y += Math::RandomRange(-2.0f, 0.0f);
					actor = ObjectPool::Instance()->Create<NoneActor>(position, Field::FieldLevel::City);
					groundContainer.push_back(actor);
				}

				x++;
			}

			z++;
		}

#ifndef _DEBUG
		//フィールドの外側の背景を作る
		//NOTE:とりあえずなので全部海にしてしまう
		const int MaxOuter = 25;
		for (int outerX = -MaxOuter; outerX < x + MaxOuter; outerX++)
		{
			for (int outerZ = -MaxOuter; outerZ < z + MaxOuter; outerZ++)
			{
				if (outerX >= 0 && outerX < x && outerZ >= 0 && outerZ < z)
					continue;

				D3DXVECTOR3 position = FieldPosition(outerX, outerZ).ConvertToWorldPosition();
				PlaceActor *actor = ObjectPool::Instance()->Create<RiverActor>(position, FieldLevel::City);
				riverContainer.push_back(actor);
			}
		}
#endif

		//メッシュコンテナ作成
		ResourceManager::Instance()->GetMesh(ActorLoader::WorldGroundTag.c_str(), groundMesh);
		groundMesh->Init();

		ResourceManager::Instance()->GetMesh(ActorLoader::SeaTag.c_str(), seaMesh);
		seaMesh->Init();
	}

	/**************************************
	海判定
	***************************************/
	bool WorldBackGroundContainer::IsSeaPlace(const FieldPosition & position) const
	{
		return Utility::IsContain(seaMap, position);
	}

	/**************************************
	アトランティス判定	
	***************************************/
	bool WorldBackGroundContainer::EnableAtlantis(const FieldPosition & position) const
	{
		//周囲8マスを含めた範囲を確認
		for (int x = -1; x <= 1; x++)
		{
			for (int z = -1; z <= 1; z++)
			{
				FieldPosition SearchPosition = FieldPosition(x, z) + position;

				if (!Utility::IsContain(seaMap, SearchPosition))
					return false;
			}
		}

		return true;
	}

	/**************************************
	アトランティスセット処理
	***************************************/
	void WorldBackGroundContainer::CreateAtlantis(const FieldPosition & position)
	{
		const D3DXVECTOR3 InitOffset = Vector3::Down * 10.0f;

		for (int x = -1; x <= 1; x++)
		{
			for (int z = -1; z <= 1; z++)
			{
				FieldPosition fieldPos = position + FieldPosition(x, z);
				D3DXVECTOR3 worldPosition = fieldPos.ConvertToWorldPosition();
				PlaceActor *actor = ObjectPool::Instance()->Create<NoneActor>(worldPosition + InitOffset, FieldLevel::City);
				groundContainer.push_back(actor);

				//海からせり上がってくるアニメーション
				Tween::Move(*actor, worldPosition + InitOffset, worldPosition, 60, EaseType::InOutCirc);

				//地形情報の更新
				auto itr = std::remove(seaMap.begin(), seaMap.end(), fieldPos);
				seaMap.erase(itr, seaMap.end());
			}
		}
	}
}