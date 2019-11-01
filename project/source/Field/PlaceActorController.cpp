//=====================================
//
//PlaceActorController.cpp
//機能:プレイスアクターコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlaceActorController.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "FieldConfig.h"
#include "../../Framework/Task/TaskManager.h"
#include "../Effect/GameParticleManager.h"
#include "Along\AlongController.h"
#include "AStar\AStarController.h"
#include "../FieldObject/PassengerController.h"

#include "../FieldObject/Actor/CityActor.h"
#include "../FieldObject/Actor/CrossJunctionActor.h"
#include "../FieldObject/Actor/CurveRoadActor.h"
#include "../FieldObject/Actor/MountainActor.h"
#include "../FieldObject/Actor/RiverActor.h"
#include "../FieldObject/Actor/StraightRoadActor.h"
#include "../FieldObject/Actor/TJunctionActor.h"
#include "../FieldObject/Actor/BridgeActor.h"
#include "../FieldObject/Actor/NoneActor.h"

#include "../FieldObject/Animation/ActorAnimation.h"

namespace Field::Actor
{
	/**************************************
	using宣言
	***************************************/
	using Model::PlaceType;
	using Model::Adjacency;

	/**************************************
	staticメンバ
	***************************************/
	const float PlaceActorController::PlacePositionOffset = 10.0f;
	const D3DXVECTOR3 PlaceActorController::PositionEmitSmog = Vector3::Up;
	const unsigned PlaceActorController::ReserveGround = 2500;

	/**************************************
	コンストラクタ
	***************************************/
	PlaceActorController::PlaceActorController()
	{
		bgContainer.reserve(ReserveGround);
		alongController = new Along::AlongController();
		aStarController = new Route::AStarController();
		passengerController = new PassengerController();

		auto onReachPassenger = std::bind(&Along::AlongController::OnReachPassenger, alongController, std::placeholders::_1);
		passengerController->SetCallbackOnReach(onReachPassenger);
	}

	/**************************************
	デストラクタ
	***************************************/
	PlaceActorController::~PlaceActorController()
	{
		SAFE_DELETE(alongController);
		SAFE_DELETE(aStarController);
		SAFE_DELETE(passengerController);

		bgContainer.clear();
		actorContainer.clear();
	}

	/**************************************
	更新処理
	***************************************/
	void PlaceActorController::Update()
	{
		alongController->Update();
		passengerController->Update();

		RiverActor::UpdateHeight();

		for (auto&& ground : bgContainer)
		{
			ground->Update();
		}

		for (auto&& actor : actorContainer)
		{
			actor.second->Update();
		}

		for (auto&& actor : poolDestroy)
		{
			actor.second->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void PlaceActorController::Draw()
	{
		//NOTE:インスタンシングで描画するために結構いじるかも
		for (auto&& ground : bgContainer)
		{
			ground->Draw();
		}

		for (auto&& actor : actorContainer)
		{
			actor.second->Draw();
		}

		for (auto&& actor : poolDestroy)
		{
			actor.second->Draw();
		}

		alongController->Draw();
		passengerController->Draw();
	}

	/**************************************
	アクターセット処理
	***************************************/
	void PlaceActorController::SetActor(const Model::PlaceModel * place, int delay)
	{
		const Model::PlaceType Type = place->GetType();

		switch (Type)
		{
		case PlaceType::Bridge:
			SetBridge(place);
			break;

		case PlaceType::Junction:
			SetJunction(place);
			break;

		case PlaceType::Mountain:
			SetMountain(place);
			SetNone(place);
			break;

		case PlaceType::River:
			SetRiver(place);
			break;

		case PlaceType::Road:
			SetRoad(place, delay);
			break;

		case PlaceType::Town:
			SetTown(place);
			SetNone(place);
			break;

		case PlaceType::None:
			SetNone(place, 2.0f);
			break;
		}
	}

	/**************************************
	アクターセット処理
	***************************************/
	void PlaceActorController::SetActor(const RouteModelPtr routeModel)
	{
		auto places = routeModel->GetAllPlaces();

		ChangeActor(places.front());
		ChangeActor(places.back());

		unsigned PlaceMax = places.size() - 1;
		for (unsigned i = 1; i < PlaceMax; i++)
		{
			if (places[i]->IsType(PlaceType::Bridge))
				continue;

			SetActor(places[i], i * 2);
		}
	}

	/**************************************
	アクター切り替え処理
	***************************************/
	void PlaceActorController::ChangeActor(const Model::PlaceModel * place)
	{
		if (place == nullptr)
			return;

		if (place->IsType(PlaceType::Town))
			return;

		//アクター破棄
		EraseFromContainer(place->ID());

		SetActor(place);
	}

	/**************************************
	アクター消滅処理
	***************************************/
	bool PlaceActorController::DestroyActor(const Model::PlaceModel * place)
	{
		unsigned placeID = place->ID();

		if (actorContainer.count(placeID) == 0)
			return false;

		GameParticleManager::Instance()->Generate(GameParticle::WhiteSmog, place->GetPosition().ConvertToWorldPosition());

		//破棄プールへ移動してアクターコンテナから削除
		poolDestroy[placeID] = std::move(actorContainer[placeID]);
		actorContainer.erase(placeID);

		//アニメーションさせて終了時に解放
		ActorAnimation::Shrink(*poolDestroy[placeID], [&, placeID]()
		{
			poolDestroy.erase(placeID);
		});

		return true;
	}

	/**************************************
	道沿いのオブジェクト成長処理
	***************************************/
	void PlaceActorController::GrowthAlongObject(const D3DXVECTOR3 & position)
	{
		alongController->OnReachPassenger(position);
	}

	/**************************************
	街が繋がった
	***************************************/
	void PlaceActorController::OnConnectedTown(const Model::PlaceModel * place)
	{
		aStarController->OnChangePlace(place);
	}

	/**************************************
	パッセンジャー出発処理
	***************************************/
	void PlaceActorController::DepartPassenger(const Model::PlaceModel * start, const Model::PlaceModel * goal)
	{
		auto route = aStarController->CalcRoute(start->GetPosition(), goal->GetPosition());
		if(route.size() != 0)
			passengerController->SetPassenger(route);
	}

	/**************************************
	ロードセット処理
	***************************************/
	void PlaceActorController::SetRoad(const Model::PlaceModel * place, int delay)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//連結情報からどのタイプの道かを判定
		std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
		StraightType straightType = IsStraight(AdjacencyType);

		//直線タイプの場合
		if (straightType != StraightType::NotStraight)
		{
			//アクター生成
			PlaceActor* actor = new StraightRoadActor(actorPos, Model::FieldLevel::City);
			AddContainer(place->ID(), actor);

			//左右に繋がるタイプなら回転させる
			if (straightType == StraightType::RightAndLeft)
				actor->Rotate(90.0f);

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::Straight);

			// 生成アニメーション
			actor->SetScale(Vector3::Zero);
			SetRoadGenerateAnimation(actor, actorPos, delay);
		}
		//カーブの場合
		else
		{
			//アクター生成
			PlaceActor* actor = new CurveRoadActor(actorPos, Model::FieldLevel::City);
			AddContainer(place->ID(), actor);

			//回転角度を決定して回転
			float rotAngle = 0.0f;

			CurveType curveType = IsCurve(AdjacencyType);
			if (curveType == CurveType::LeftAndForward)
				rotAngle = -90.0f;
			else if (curveType == CurveType::BackAndRight)
				rotAngle = 90.0f;
			else if (curveType == CurveType::ForwardAndRight)
				rotAngle = 180.0f;

			actor->Rotate(rotAngle);

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::Curve);

			// 生成アニメーション
			actor->SetScale(Vector3::Zero);
			SetRoadGenerateAnimation(actor, actorPos, delay);
		}

		//A*に登録
		aStarController->OnChangePlace(place);
	}

	/**************************************
	タウンセット処理
	***************************************/
	void PlaceActorController::SetTown(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//アクター生成
		PlaceActor* actor = new CityActor(actorPos, Model::FieldLevel::City);

		// 生成アニメーション
		ActorAnimation::ExpantionYAndReturnToOrigin(*actor);

		AddContainer(place->ID(), actor);

		//A*に登録
		aStarController->OnChangePlace(place);
	}

	/**************************************
	川セット処理
	***************************************/
	void PlaceActorController::SetRiver(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//アクター生成
		PlaceActor* actor = new RiverActor(actorPos, Model::FieldLevel::City);

		//アニメーション
		ActorAnimation::ExpantionYAndReturnToOrigin(*actor);

		bgContainer.push_back(std::unique_ptr<PlaceActor>(actor));
	}

	/**************************************
	ブリッジセット処理
	***************************************/
	void PlaceActorController::SetBridge(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//アクター生成
		PlaceActor* actor = new BridgeActor(actorPos, Model::FieldLevel::City);

		//回転角度を決定
		std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
		StraightType straightType = IsStraight(AdjacencyType);

		float rotateAngle = straightType == StraightType::BackAndForward ? 90.0f : 0.0f;

		//回転
		actor->Rotate(rotateAngle);

		// 生成アニメーション
		ActorAnimation::FallAndExpantion(*actor);

		AddContainer(place->ID(), actor);

		//A*に登録
		aStarController->OnChangePlace(place);
	}

	/**************************************
	交差点セット処理
	***************************************/
	void PlaceActorController::SetJunction(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		std::vector<Adjacency> adjacencyTypeList = place->GetConnectingAdjacency();

		//十字路のアクター作成
		if (adjacencyTypeList.size() == 4)
		{
			PlaceActor *actor = new CrossJunctionActor(actorPos, Model::FieldLevel::City);

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::CrossJunction);

			// 生成アニメーション
			ActorAnimation::RotateAndExpantion(*actor);
			AddContainer(place->ID(), actor);

		}
		//T字路のアクター生成
		else
		{
			PlaceActor* actor = new TJunctionActor(actorPos, Model::FieldLevel::City);

			TjunctionType junctionType = IsTjunction(adjacencyTypeList);
			float rotAngle = 0.0f;

			if (junctionType == TjunctionType::ExceptRight)
				rotAngle = 90.0f;
			else if (junctionType == TjunctionType::ExceptForward)
				rotAngle = 180.0f;
			else if (junctionType == TjunctionType::ExceptLeft)
				rotAngle = 270.0f;

			actor->Rotate(rotAngle);

			AddContainer(place->ID(), actor);
			
			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::T_Junction);

			// 生成アニメーション
			ActorAnimation::RotateAndExpantion(*actor);
		}

		//A*に登録
		aStarController->OnChangePlace(place);
	}

	/**************************************
	山セット処理
	***************************************/
	void PlaceActorController::SetMountain(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		PlaceActor *actor = new MountainActor(actorPos, Model::FieldLevel::City);

		//回転
		float rotateAngle = Math::RandomRange(0, 4) * 90.0f;
		actor->Rotate(rotateAngle);

		//アニメーション
		ActorAnimation::ExpantionYAndReturnToOrigin(*actor);

		AddContainer(place->ID(), actor);
	}

	/**************************************
	Noneセット処理
	***************************************/
	void PlaceActorController::SetNone(const Model::PlaceModel * place, float randomRange)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//真っ平らだと不自然なので高さに少し凹凸をつける
		actorPos.y += Math::RandomRange(-randomRange, 0.0f);

		PlaceActor* actor = new NoneActor(actorPos, Model::FieldLevel::City);

		// 生成アニメーション
		ActorAnimation::RotateAndExpantion(*actor);

		bgContainer.push_back(std::unique_ptr<PlaceActor>(actor));
	}

	/**************************************
	コンテナ追加処理
	***************************************/
	void PlaceActorController::AddContainer(unsigned key, PlaceActor * actor)
	{
		//重複確認
		EraseFromContainer(key);

		actorContainer.emplace(key, std::unique_ptr<PlaceActor>(actor));
	}

	/**************************************
	コンテナからの削除処理
	***************************************/
	bool PlaceActorController::EraseFromContainer(unsigned key)
	{
		if (actorContainer.count(key) == 0)
			return false;

		//アクターコンテナから
		actorContainer.erase(key);

		return true;
	}

	/**************************************
	道生成時のアニメーションセット処理
	***************************************/
	void Field::Actor::PlaceActorController::SetRoadGenerateAnimation(PlaceActor * actor, const D3DXVECTOR3 actorPos, int delay)
	{
		if (delay == 0)
			ActorAnimation::FallAndExpantion(*actor, [=]()
		{
			GameParticleManager::Instance()->Generate(GameParticle::ColorfulDebis, actorPos + PositionEmitSmog);
		});

		else
		{
			TaskManager::Instance()->CreateDelayedTask(delay, [=]()
			{
				ActorAnimation::FallAndExpantion(*actor, [=]()
				{
					GameParticleManager::Instance()->Generate(GameParticle::ColorfulDebis, actorPos + PositionEmitSmog);
				});
			});
		}
	}
}