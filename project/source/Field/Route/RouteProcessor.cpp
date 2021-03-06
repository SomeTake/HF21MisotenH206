
//=====================================
//
//RouteProcessor.cpp
//機能:ルートモデルを操作するクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RouteProcessor.h"
#include "RouteModel.h"
#include "../Place/FieldPlaceModel.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using宣言
	***************************************/
	using cpplinq::from;
	using cpplinq::contains;

	/**************************************
	コンストラクタ
	***************************************/
	RouteProcessor::RouteProcessor(std::function<void(const PlaceModel*)>& onChangePlaceType)
	{
		this->onChangePlaceType = onChangePlaceType;
	}

	/**************************************
	新しく作ったルートに対して隣接しているルートと連結させて加工する
	***************************************/
	void RouteProcessor::Process(RouteModelPtr & model, RouteContainer & routeContainer, std::vector<PlaceModel*> *ignoreList)
	{
		//分割したルートのリスト
		RouteContainer divideList;

		//無視リストがNULLなら作成
		if (ignoreList == NULL)
		{
			ignoreList = &model->route;
		}

		//対象のルートのPlaceに対して1個ずつ隣接ルートを確認する
		std::vector<PlaceModel*> route = model->route;
		for (auto&& place : route)
		{
			//橋の場合は判定しない
			if (place->IsType(PlaceType::Bridge))
				continue;

			auto connectTargets = place->GetConnectTargets();
			
			for (auto&& target : connectTargets)
			{
				//連結対象な見つからなかったのでコンティニュー
				if (target == nullptr)
					continue;

				//連結対象が無視リストに含まれていたらコンティニュー
				if (Utility::IsContain(*ignoreList, target))
					continue;

				_Process(model, place, target, routeContainer, divideList);
			}

			//ルートを分割した時点で正常にループできなくなるのでブレイク
			if(!divideList.empty())
				break;
		}

		//分割が行われていなかったらルートコンテナに追加
		if (divideList.empty())
		{
			routeContainer.push_back(model);
		}
		//分割が行われていたら再帰的に加工処理
		else
		{
			for (auto&& divModel : divideList)
			{
				Process(divModel, routeContainer, ignoreList);
			}
		}
	}

	/**************************************
	新しく作ったルートを端点で連結させる
	***************************************/
	void RouteProcessor::ConnectWithEdge(RouteModelPtr & model, RouteContainer & routeContainer)
	{
		//始点の連結を確認
		PlaceModel* start = model->edgeStart;
		if (start->IsType(PlaceType::Road) || start->IsType(PlaceType::Junction))
		{
			_ConnectWithEdge(model, start, routeContainer, model->GetFirst());
			start->AddDirection(model->route.front());
		}

		//終点の連結を確認
		PlaceModel* end = model->edgeEnd;
		if (end->IsType(PlaceType::Road) || end->IsType(PlaceType::Junction))
		{
			_ConnectWithEdge(model, end, routeContainer, model->GetLast());
			end->AddDirection(model->route.back());
		}
	}

	/**************************************
	ルートを指定したプレイスで分割する
	***************************************/
	RouteContainer RouteProcessor::Divide(RouteModelPtr & model, PlaceModel * junction, RouteContainer & routeContainer)
	{
		//分割後は使用しなくなるのでフラグを立てて、プレイスの所属を解除
		model->SetUnused(true);
		model->BreakAway();

		//交差点を基準にしてルートを分割
		std::vector<PlaceModel*> route = model->route;
		auto itrJunction = std::find(route.begin(), route.end(), junction);

		std::vector<PlaceModel*> firstHalf, secondHalf;
		firstHalf.assign(route.begin(), itrJunction);
		secondHalf.assign(itrJunction + 1, route.end());		//Junctionも含めないのでイテレータを+1

		//前半のRouteModelを作成
		RouteModelPtr first = RouteModel::Create(model->onConnectedTown, firstHalf);
		first->SetEdge(model->edgeStart);
		first->SetEdge(junction);

		//後半のRouteModelを作成
		RouteModelPtr second = RouteModel::Create(model->onConnectedTown, secondHalf);
		second->SetEdge(junction);
		second->SetEdge(model->edgeEnd);

		//分割前のルートの隣接ルートを取得
		std::vector<AdjacentRoute> adjacencies = model->adjacentRoute;

		//分割したルート同士の隣接情報作成
		first->AddAdjacency(junction, junction, second);
		second->AddAdjacency(junction, junction, first);

		//分割前に隣接していたルートに対して隣接情報を追加
		for (auto&& adjacency : adjacencies)
		{
			PlaceModel* connection = adjacency.start;

			//firstとsecondのどちらにconnectionが含まれているか判定
			RouteModelPtr opponent = from(firstHalf) >> contains(connection) ? first : second;

			std::shared_ptr<RouteModel> sptr = adjacency.route.lock();
			if (sptr)
			{
				sptr->AddAdjacency(adjacency.end, adjacency.start, opponent);
				opponent->AddAdjacency(adjacency.start, adjacency.end, sptr);
			}
		}

		//分割後のRouteModelをリストに追加
		RouteContainer routeList{ first, second };

		return routeList;
	}

	/**************************************
	加工処理（内部）
	***************************************/
	void RouteProcessor::_Process(RouteModelPtr& model, PlaceModel* place, PlaceModel* target, RouteContainer& routeContainer, RouteContainer& divList)
	{
		//対象のPlaceを交差点にして分割
		place->SetType(PlaceType::Junction);
		divList = Divide(model, place, routeContainer);

		place->AddDirection(target);
		target->AddDirection(place);

		//繋がった相手も必要であれば分割する
		target->SetType(PlaceType::Junction);
		RouteContainer subDivList;
		if (target->GetPrevType() == PlaceType::Road)
		{
			RouteModelPtr opponent = target->GetConnectingRoute();
			subDivList = Divide(opponent, target, routeContainer);
		}
		else
		{
			subDivList = target->GetConnectingRoutes();
		}

		//繋がったルート同士を隣接メンバとして保存
		for (auto&& own : divList)
		{
			for (auto&& other : subDivList)
			{
				own->AddAdjacency(place, target, other);
				other->AddAdjacency(target, place, own);
			}
		}

		//相手を分割していればRouteContainerに追加
		if (subDivList.size() > 1)
		{
			std::copy(subDivList.begin(), subDivList.end(), std::back_inserter(routeContainer));
		}

		//所属を更新
		RouteContainer belongList = target->GetConnectingRoutes();
		place->BelongRoute(belongList);

		target->BelongRoute(divList);

		//交差点と連結対象のオブジェクトを設定
		onChangePlaceType(place);
		onChangePlaceType(target);
	}

	/**************************************
	連結処理（内部）
	***************************************/
	void RouteProcessor::_ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer, PlaceModel *edge)
	{
		//相手を交差点に変える必要があるか確認
		Adjacency adjacency = place->IsAdjacent(edge);
		std::vector<Adjacency> direction = place->GetConnectingAdjacency();
		bool shouldChangeJunction = !Utility::IsContain(direction, adjacency);

		if (shouldChangeJunction)
		{
			place->SetType(PlaceType::Junction);
			place->AddDirection(adjacency);
			onChangePlaceType(place);

			if (place->GetPrevType() == PlaceType::Road)
			{
				RouteContainer targetList = place->GetConnectingRoutes();

				//取得した所属リストに新しく作ったルートが含まれるので削除
				targetList.erase(std::remove(targetList.begin(), targetList.end(), model));

				//相手を分割
				RouteContainer divList = Divide(*targetList.begin(), place, routeContainer);
				std::copy(divList.begin(), divList.end(), std::back_inserter(routeContainer));
			}
		}

		//連結相手と作ったルートの隣接情報を作成
		RouteContainer routeList = place->GetConnectingRoutes();
		routeList.erase(std::remove(routeList.begin(), routeList.end(), model));
		for (auto&& route : routeList)
		{
			model->AddAdjacency(edge, place, route);
			route->AddAdjacency(place, edge, model);
		}
	}
}