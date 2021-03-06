//=====================================
//
//RouteModel.cpp
//機能:繋がった道を表すモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RouteModel.h"
#include "../Place/FieldPlaceModel.h"
#include "../../../Library/cppLinq/cpplinq.hpp"
#include "../../../Framework/Pattern/Delegate.h"
#include "../Place/FieldTownModel.h"
#include "../../../Framework/Tool/DebugWindow.h"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using宣言
	***************************************/
	using cpplinq::last_or_default;
	using cpplinq::from;
	using cpplinq::contains;

	/**************************************
	static変数
	***************************************/
	unsigned RouteModel::incrementID = 0;

	/**************************************
	コンストラクタ
	***************************************/
	RouteModel::RouteModel(CallbackConnect& onConnectTown) :
		edgeStart(nullptr), edgeEnd(nullptr),
		uniqueID(incrementID++),
		isUnused(false),
		onConnectedTown(onConnectTown)
	{

	}

	/**************************************
	等地比較演算子
	***************************************/
	bool RouteModel::operator==(const RouteModel & rhs) const
	{
		return route == rhs.route;
	}

	/**************************************
	スマートポインタ作成処理
	***************************************/
	RouteModelPtr RouteModel::Create(CallbackConnect& onConnectTown)
	{
		RouteModelPtr ptr = std::make_shared<RouteModel>(onConnectTown);
		return ptr;
	}

	/**************************************
	スマートポインタ作成処理
	***************************************/
	RouteModelPtr RouteModel::Create(CallbackConnect& onConnectTown, const std::vector<PlaceModel*>& placeVector)
	{
		RouteModelPtr ptr = std::make_shared<RouteModel>(onConnectTown);

		ptr->route.assign(placeVector.begin(), placeVector.end());

		for (auto&& place : ptr->route)
		{
			place->BelongRoute(ptr);
		}

		return ptr;
	}

	/**************************************
	デストラクタ
	***************************************/
	RouteModel::~RouteModel()
	{
		adjacentRoute.clear();
		route.clear();
	}

	/**************************************
	更新処理
	***************************************/
	void RouteModel::Update()
	{
		//使用されていないルートモデルを隣接リストから削除
		auto itr = std::remove_if(adjacentRoute.begin(), adjacentRoute.end(), [](AdjacentRoute& adjacaency)
		{
			return adjacaency.route.expired();
		});
		adjacentRoute.erase(itr, adjacentRoute.end());
	}

	/**************************************
	デバッグ情報表示
	***************************************/
	void RouteModel::ViewDebug() const
	{
		Debug::Text("route id : %d", uniqueID);

		FieldPosition startPos = edgeStart->GetPosition();
		FieldPosition endPos = edgeEnd->GetPosition();
		Debug::Text("start : %d, %d / end : %d, %d", startPos.x, startPos.z, endPos.x, endPos.z);

		Debug::Text("cntPlace : %d", route.size());

		Debug::Text("cntAdjacent : %d", adjacentRoute.size());
		for (auto&& adjacent : adjacentRoute)
		{
			auto ptr = adjacent.route.lock();
			Debug::Text("%d, ", ptr->uniqueID);
			Debug::SameLine();
		}
		Debug::NewLine();
	}

	/**************************************
	道となるプレイス追加
	***************************************/
	void RouteModel::AddRoad(PlaceModel * place)
	{
		edgeEnd = place;
		route.push_back(place);
		place->BelongRoute(shared_from_this());
	}

	/**************************************
	プレイスの所属解除
	***************************************/
	void RouteModel::BreakAway()
	{
		//自身に所属しているプレイスの所属を解除
		edgeStart->ExitRoute(shared_from_this());
		edgeEnd->ExitRoute(shared_from_this());
		for (auto&& place : route)
		{
			place->ExitRoute(shared_from_this());
		}
	}

	/**************************************
	隣接ルート追加
	***************************************/
	void RouteModel::AddAdjacency(PlaceModel * junction, PlaceModel * connectTarget, std::shared_ptr<RouteModel> opponent)
	{
		if (*opponent == *this)
			return;

		for (auto&& adjacenct : adjacentRoute)
		{
			std::shared_ptr<RouteModel> sptr = adjacenct.route.lock();

			if (sptr && *sptr == *opponent)
				return;
		}

		adjacentRoute.push_back(AdjacentRoute(junction, connectTarget, opponent));
	}

	/**************************************
	端点設定
	***************************************/
	void RouteModel::SetEdge(PlaceModel * edge)
	{
		if (edgeStart == nullptr)
			edgeStart = edge;
		else
			edgeEnd = edge;

		edge->BelongRoute(shared_from_this());
	}

	/**************************************
	端点設定
	***************************************/
	void RouteModel::SetEdge()
	{
		//始点から端点を設定
		PlaceModel* first = route.front();
		_SetEdge(first);

		//終点から端点を設定
		PlaceModel* last = route.back();
		_SetEdge(last);

		//各プレイスの方向を決定
		unsigned routeSize = route.size();

		if (routeSize != 1)
		{
			first->AddDirection(first->IsAdjacent(edgeStart));
			first->AddDirection(first->IsAdjacent(route[1]));

			for (unsigned i = 1; i < routeSize - 1; i++)
			{
				PlaceModel* place = route[i];
				place->AddDirection(place->IsAdjacent(route[i - 1]));
				place->AddDirection(place->IsAdjacent(route[i + 1]));
			}

			last->AddDirection(last->IsAdjacent(route[routeSize - 2]));
			last->AddDirection(last->IsAdjacent(edgeEnd));
		}
		else
		{
			first->AddDirection(first->IsAdjacent(edgeStart));
			first->AddDirection(first->IsAdjacent(edgeEnd));
		}
	}

	/**************************************
	他方の端点取得
	***************************************/
	PlaceModel * RouteModel::GetOtherEdge(const PlaceModel * edge)
	{
		if (edgeStart == edge)
			return edgeEnd;
		else
			return edgeStart;
	}

	/**************************************
	繋がっている街を取得
	***************************************/
	PlaceModel * RouteModel::GetConnectedTown(const PlaceModel * self)
	{
		if (edgeStart->IsType(PlaceType::Town) && edgeStart != self)
			return edgeStart;

		if (edgeEnd->IsType(PlaceType::Town) && edgeEnd != self)
			return edgeEnd;

		return nullptr;
	}

	/**************************************
	繋がっている街を取得
	***************************************/
	int RouteModel::FindLinkedTown(TownModel * root, std::vector<unsigned> & searchedRoute)
	{
		int cntTown = 0;

		//対象に繋がっている街を確認
		searchedRoute.push_back(uniqueID);

		const PlaceModel* town = this->GetConnectedTown(root->GetPlace());
		if (town != nullptr)
		{
			cntTown++;

			//経路を保存
			root->AddLinkedTown(town);
		}

		//隣接しているルートに対して再帰的に探索
		for (auto&& adjacency : this->adjacentRoute)
		{
			RouteModelPtr ptr = adjacency.route.lock();

			if (!ptr)
				continue;

			if (Utility::IsContain(searchedRoute, ptr->uniqueID))
				continue;

			cntTown += ptr->FindLinkedTown(root, searchedRoute);
		}


		return cntTown;
	}

	/**************************************
	使用判定セット処理
	***************************************/
	void RouteModel::SetUnused(bool use)
	{
		isUnused = use;
	}

	/**************************************
	使用判定
	***************************************/
	bool RouteModel::IsUnused()
	{
		return isUnused;
	}

	/**************************************
	全プレイス取得
	***************************************/
	const std::vector<const PlaceModel*> RouteModel::GetAllPlaces(const PlaceModel* start) const
	{
		std::vector<const PlaceModel*> out;
		out.reserve(route.size() + 2);

		if (start == edgeEnd)
		{
			out.push_back(edgeEnd);
			std::copy(route.rbegin(), route.rend(), std::back_inserter(out));
			out.push_back(edgeStart);
		}
		else
		{
			out.push_back(edgeStart);

			std::copy(route.begin(), route.end(), std::back_inserter(out));
			out.push_back(edgeEnd);
		}

		return out;
	}

	/**************************************
	始点取得処理
	***************************************/
	PlaceModel * RouteModel::GetFirst() const
	{
		return route.front();
	}

	/**************************************
	終点取得処理
	***************************************/
	PlaceModel * RouteModel::GetLast() const
	{
		return route.back();
	}

	/**************************************
	端点設定（内部処理）
	***************************************/
	void RouteModel::_SetEdge(PlaceModel* place)
	{
		//連結相手を取得
		PlaceModel* edge = nullptr;
		auto opponents = place->GetEdgeOpponents();
		for (auto&& opponent : opponents)
		{
			//if (opponent != edgeEnd && opponent != edgeStart)
			{
				edge = opponent;
				break;
			}
		}

		SetEdge(edge);
		edge->BelongRoute(shared_from_this());

		//街なら出口を増やす
		if (edge->IsType(PlaceType::Town))
		{
			//方向追加
			edge->AddDirection(edge->IsAdjacent(place));

			onConnectedTown(edge, place);
		}
	}
}