//=====================================
//
//PlaceContainer.cpp
//機能:プレイスコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldPlaceContainer.h"
#include "FieldPlaceModel.h"
#include "FieldTownModel.h"
#include "FieldJunctionModel.h"
#include "../../../Framework/String/String.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Tool/ProfilerCPU.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

#include <fstream>
#include <string>

#ifdef DEBUG_PLACEMODEL
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#endif

namespace Field::Model
{
	/**************************************
	グローバル変数
	***************************************/

	/**************************************
	コンストラクタ
	***************************************/
	PlaceContainer::PlaceContainer() :
		placeRowMax(0),
		placeColumMax(0),
		initialized(false),
		trafficJamRate(0.0f),
		trafficJamBias(0.0f),
		onDepartPassenger(nullptr),
		fieldLinkLevel(0),
		pureFieldLinkLevel(0)
	{
		placeVector.reserve(PlaceMax);

#ifdef DEBUG_PLACEMODEL

#endif
	}

	/**************************************
	デストラクタ
	***************************************/
	PlaceContainer::~PlaceContainer()
	{
		Clear();
	}

	/**************************************
	更新処理
	***************************************/
	void PlaceContainer::Update()
	{
		if (!initialized)
			return;

		for (auto&& town : townContainer)
		{
			town.second->Update();
		}
	}

	/**************************************
	クリア処理
	***************************************/
	void Field::Model::PlaceContainer::Clear()
	{
		Utility::DeleteContainer(placeVector);
		Utility::DeleteMap(townContainer);
		Utility::DeleteMap(junctionContainer);

		initialized = false;
		fieldLinkLevel = 0;
		pureFieldLinkLevel = 0;
	}

#ifdef DEBUG_PLACEMODEL
	/**************************************
	描画処理
	***************************************/
	void PlaceContainer::DrawDebug()
	{
		if (!initialized)
			return;

		
	}
#endif

	/**************************************
	プレイス取得処理
	***************************************/
	PlaceModel * PlaceContainer::GetPlace(int x, int z)
	{
		if (x < 0 || x >= placeRowMax)
			return nullptr;

		if (z < 0 || z >= placeColumMax)
			return nullptr;

		return placeVector[placeColumMax * z + x];
	}

	/**************************************
	プレイス取得処理
	***************************************/
	PlaceModel* PlaceContainer::GetPlace(const FieldPosition& position)
	{
		if (position.x < 0 || position.x >= placeRowMax)
			return nullptr;

		if (position.z < 0 || position.z >= placeColumMax)
			return nullptr;

		return placeVector[placeColumMax * position.z + position.x];
	}

	/**************************************
	前プレイス取得処理
	***************************************/
	std::vector<PlaceModel*> Field::Model::PlaceContainer::GetAllPlaces() const
	{
		using cpplinq::from;
		using cpplinq::where;
		using cpplinq::to_vector;

		std::vector<PlaceModel*> out = 
			from(placeVector)
			>> where([](PlaceModel* model)
		{
			return !model->IsType(PlaceType::None);
		})
			>> to_vector();

		return out;
	}

	/**************************************
	CSV読み込み処理
	***************************************/
	void PlaceContainer::LoadCSV(const char * filePath)
	{
		//初期化済みであればリターン
		if (initialized)
			return;

		//CSVファイルを読み込み
		std::ifstream stream(filePath);

		std::string line;			//CSVを1行ずつ読むバッファ
		const char Delim = ',';		//区切り文字
		int x = 0;					//PlaceのX位置
		int z = 0;					//PlaceのZ位置

		//CSVの終わりまで読み込み続ける
		while (std::getline(stream, line))
		{
			//1行分読み込んだデータを区切り文字で分割する
			std::vector<std::string> subStr;
			String::Split(subStr, line, Delim);

			x = 0;

			//分割したデータ毎にPlaceModelを作成
			for (auto&& str : subStr)
			{
				PlaceType type = IntToPlaceType(std::stoi(str));
				PlaceModel *place = new PlaceModel(type, x, z);
				placeVector.push_back(place);

				x++;
			}

			z++;
		}

		//コンテナの行数と列数を保存
		placeRowMax = x;
		placeColumMax = z;

		//隣接情報作成
		MakeAdjacency();

		//初期化完了
		initialized = true;
	}

	/**************************************
	行、列の最大数取得
	***************************************/
	FieldPosition Field::Model::PlaceContainer::GetPlaceBorder() const
	{
		return FieldPosition(placeRowMax, placeColumMax);
	}

	/**************************************
	街が道と繋がったときの処理
	***************************************/
	void Field::Model::PlaceContainer::OnConnectedTown(const PlaceModel * town, const PlaceModel *gate)
	{
		unsigned placeID = town->ID();

		//登録確認
		if (townContainer.count(placeID) == 0)
		{
			townContainer.emplace(placeID, new TownModel(town, onDepartPassenger, onStartMorph));
		}

		townContainer[placeID]->AddGate(gate);
	}

	/**************************************
	交差点が作られたときの処理
	***************************************/
	void Field::Model::PlaceContainer::OnCreateJunction(const PlaceModel * place)
	{
		unsigned placeID = place->ID();

		//登録確認
		if (junctionContainer.count(placeID) == 0)
		{
			junctionContainer.emplace(placeID, new JunctionModel(place));
		}
	}

	/**************************************
	リンクレベルの計算
	***************************************/
	void Field::Model::PlaceContainer::CalcLinkLevel()
	{
		fieldLinkLevel = 0;
		pureFieldLinkLevel = 0;

		for (auto&& town : townContainer)
		{
			town.second->FindLinkedTown();
			fieldLinkLevel += town.second->LinkLevel();
			pureFieldLinkLevel += town.second->PureLinkLevel();
		}
	}

	/**************************************
	AI発展レベル計算
	***************************************/
	float Field::Model::PlaceContainer::CalcDevelopmentLevelAI(float bonus)
	{
		float developLevel = 0.0f;
		for (auto&& town : townContainer)
		{
			developLevel += town.second->LinkLevel() / 3.0f;
		}

		return developLevel;
	}

	/**************************************
	街全体のリンクレベル増加
	***************************************/
	void Field::Model::PlaceContainer::AddAllLinkLevel(int num)
	{
		for (auto&& town : townContainer)
		{
			town.second->AddLinkLevel(num);
		}
	}

	/**************************************
	街一つのリンクレベル増加
	***************************************/
	void Field::Model::PlaceContainer::AddLinkLevel(int num)
	{
		//ランダムに選択された街にリンクレベルを足す
		//無作為に抽出するいい方法が思い浮かばなかった
		int randomIndex = Math::RandomRange(0, (int)(townContainer.size()));
		int index = 0;
		for (auto&& town : townContainer)
		{
			if (index++ != randomIndex)
				continue;

			town.second->AddLinkLevel(num);
			return;
		}
	}

	/**************************************
	混雑度増加バイアス設定処理
	***************************************/
	void Field::Model::PlaceContainer::SetTrafficjamBias(float bias)
	{
		trafficJamBias = bias;
	}

	/**************************************
	破壊対象プレイス取得処理
	***************************************/
	const PlaceModel * Field::Model::PlaceContainer::GetDestroyTarget()
	{
		using cpplinq::from;
		using cpplinq::where;
		using cpplinq::to_vector;

		auto townVector = from(placeVector)
			>> where([](auto& place)
		{
			return place->IsType(PlaceType::Town);
		})
			>> to_vector();

		int randomIndex = Math::RandomRange(0, (int)townVector.size() - 1);
		return townVector[randomIndex];
	}

	/**************************************
	街を作れるプレイス取得処理
	***************************************/
	const PlaceModel * Field::Model::PlaceContainer::GetNonePlace(std::vector<PlaceModel*> *ignoreList)
	{
		using cpplinq::from;
		using cpplinq::where;
		using cpplinq::to_vector;
		using cpplinq::except;

		auto noneVector = from(placeVector)
			>> where([](auto& place)
		{
			return place->IsVacant();
		})
			>> to_vector();

		if (ignoreList != nullptr)
		{
			//無視リストを除外
			noneVector = from(noneVector)
				>> except(from(*ignoreList))
				>> to_vector();
		}

		int randomIndex = Math::RandomRange(0, (int)(noneVector.size() - 1));
		return noneVector[randomIndex];
	}

	/**************************************
	街破壊処理
	***************************************/
	void Field::Model::PlaceContainer::DestroyTown(const PlaceModel * target)
	{
		auto itrPlace = std::find(placeVector.begin(), placeVector.end(), target);

		if (itrPlace == placeVector.end())
			return;

		PlaceModel *place = *itrPlace;

		//所属をリセット
		RouteContainer belongRoute = place->GetConnectingRoutes();
		for (auto&& route : belongRoute)
		{
			place->ExitRoute(route);
		}

		//PlaceModelをNoneタイプに変化
		(*itrPlace)->SetType(PlaceType::None);

		//TownModel削除
		SAFE_DELETE(townContainer[target->ID()]);
		townContainer.erase(target->ID());
	}

	/**************************************
	街作成
	***************************************/
	void Field::Model::PlaceContainer::CreateTown(const PlaceModel * target)
	{
		auto itrPlace = std::find(placeVector.begin(), placeVector.end(), target);

		if (itrPlace == placeVector.end())
			return;

		PlaceModel* place = *itrPlace;
		place->SetType(PlaceType::Town);
	}

	/**************************************
	アトランティス作成
	***************************************/
	std::vector<const PlaceModel*> Field::Model::PlaceContainer::CreateAtlantis(const PlaceModel * target)
	{
		auto itrPlace = std::find(placeVector.begin(), placeVector.end(), target);
		std::vector<const PlaceModel*> output;

		if (itrPlace == placeVector.end())
			return output;

		PlaceModel* place = *itrPlace;
		place->SetType(PlaceType::Town);

		//周囲8マスの渦潮を削除
		FieldPosition center = target->GetPosition();
		for (int x = -1; x <= 1; x++)
		{
			for (int z = -1; z <= 1; z++)
			{
				FieldPosition pos = center + FieldPosition(x, z);
				auto itr = std::find_if(placeVector.begin(), placeVector.end(), [&](PlaceModel* model)
				{
					return model->GetPosition() == pos;
				});

				if (itr == placeVector.end())
					continue;

				PlaceModel *model = *itr;
				//渦潮ならNoneに戻して追加
				if (model->IsType(PlaceType::Mountain))
				{
					model->SetType(PlaceType::None);
					output.push_back(model);
				}
				//道か交差点なら追加
				else if (model->IsType(PlaceType::Road) || model->IsType(PlaceType::Junction))
				{
					output.push_back(model);
				}
			}
		}

		return output;
	}

	/**************************************
	パッセンジャー出発ファンクタ設定
	***************************************/
	void Field::Model::PlaceContainer::SetDepartPassengerFanctor(const TownAction & action)
	{
		onDepartPassenger = action;
	}

	/**************************************
	モーフィングファンクタ設定
	***************************************/
	void Field::Model::PlaceContainer::SetMorphingFantor(const MorphAction & action)
	{
		onStartMorph = action;
	}

	/**************************************
	隣接情報作成
	***************************************/
	void PlaceContainer::MakeAdjacency()
	{
		for (int z = 0; z < placeColumMax; z++)
		{
			for (int x = 0; x < placeColumMax; x++)
			{
				//対象のプレイスの隣接プレイスをそれぞれ取得
				PlaceModel* back = GetPlace(x, z - 1);
				PlaceModel* left = GetPlace(x - 1, z);
				PlaceModel* forward = GetPlace(x, z + 1);
				PlaceModel* right = GetPlace(x + 1, z);

				//隣接プレイス設定
				PlaceModel *place = GetPlace(x, z);
				place->AddAdjacency(back, Adjacency::Back);
				place->AddAdjacency(left, Adjacency::Left);
				place->AddAdjacency(forward, Adjacency::Forward);
				place->AddAdjacency(right, Adjacency::Right);
			}
		}
	}

	//=====================================
	// すべての町の発展レベルを取得する
	//=====================================
	std::vector<PlaceData> PlaceContainer::GetAllTownLevel()
	{
		std::vector<PlaceData> ret;
		ret.reserve(townContainer.size());

		PlaceData data;
		int i = 0;
		for (auto& model : townContainer)
		{
			data = model.second->GetPlaceData();
			ret.push_back(data);
		}

		return ret;
	}

	/**************************************
	リンクレベル取得
	***************************************/
	int Field::Model::PlaceContainer::GetLinkLevel()
	{
		return fieldLinkLevel;
	}

	/**************************************
	リンクレベル取得(補正なし)
	***************************************/
	int Field::Model::PlaceContainer::GetPureLinkLevel() const
	{
		return pureFieldLinkLevel;
	}
}