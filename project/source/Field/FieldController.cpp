//=====================================
//
//FieldController.cpp
//機能:フィールドコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldController.h"
#include "FieldCursor.h"
#include "FieldGround.h"
#include "Place\FieldPlaceContainer.h"
#include "Place\OperatePlaceContainer.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "Route\RouteProcessor.h"

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

namespace Field
{
	/**************************************
	コンストラクタ
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder),
		inputRepeatCnt(0)
	{
		//インスタンス作成
		cursor = new FieldCursor(PlaceOffset);
		ground = new FieldGround();
		placeContainer = new Model::PlaceContainer();
		operateContainer = new Model::OperatePlaceContainer();

		//ステートマシン作成
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState;
		fsm[State::Develop] = new UseItemState();

		//ステート初期化
		ChangeState(State::Idle);
	}

	/**************************************
	デストラクタ
	***************************************/
	FieldController::~FieldController()
	{
		SAFE_DELETE(cursor);
		SAFE_DELETE(ground);
		SAFE_DELETE(placeContainer);
		SAFE_DELETE(operateContainer);

		routeContainer.clear();

		//ステートマシン削除
		Utility::DeleteContainer(fsm);
	}

	/**************************************
	更新処理
	***************************************/
	void FieldController::Update()
	{
		cursor->Update();
		placeContainer->Update();
	}

	/**************************************
	描画処理
	***************************************/
	void FieldController::Draw()
	{
		ground->Draw();

		placeContainer->Draw();

		//カーソルには透過オブジェクトが含まれるので最後に描画
		cursor->Draw();

		Debug::Log("ControllerState:%d", current);
	}

	/**************************************
	入力確認処理
	TODO：読み込むデータを選択できるようにする
	***************************************/
	void FieldController::Load()
	{
		placeContainer->LoadCSV("data/FIELD/sample01.csv");

		//カーソルのフィールドの中央へ設定
		FieldPosition border = placeContainer->GetPlaceBorder();
		cursor->SetModelPosition(border.x / 2, border.z / 2);
	}

	/**************************************
	入力確認処理
	***************************************/
	void FieldController::CheckInput()
	{
		//トリガー確認
		float triggerX = 0.0f, triggerZ = 0.0f;

		triggerX = Input::GetTriggerHorizontal();
		triggerZ = Input::GetTriggerVertical();

		//リピート確認
		float repeatX = 0.0f, repeatZ = 0.0f;
		if((Input::GetPressHorizontail() != 0.0f || Input::GetPressVertical() != 0.0f))
		{
			inputRepeatCnt++;
			if (inputRepeatCnt >= InputLongWait && inputRepeatCnt % InputShortWait == 0)
			{
				repeatX = Input::GetPressHorizontail();
				repeatZ = Input::GetPressVertical();
			}
		}
		else
		{
			inputRepeatCnt = 0;
		}

		//カーソルを移動
		float x = Math::Clamp(-1.0f, 1.0f, triggerX + repeatX);
		float z = Math::Clamp(-1.0f, 1.0f, triggerZ + repeatZ);
		cursor->Move((int)x, (int)z);

		//現在のステートの更新処理を実行
		State next = state->OnUpdate(*this);
		if (next != current)
		{
			ChangeState(next);
		}
	}

	/**************************************
	カーソル取得処理
	***************************************/
	GameObject * FieldController::GetFieldCursor()
	{
		return cursor;
	}

	/**************************************
	ステート切り替え処理
	***************************************/
	void FieldController::ChangeState(State next)
	{
		if (fsm[next] == NULL)
			return;

		current = next;
		state = fsm[next];
		state->OnStart(*this);
	}

	/**************************************
	カーソル位置のプレイスを取得
	***************************************/
	Model::PlaceModel * FieldController::GetPlace()
	{
		return placeContainer->GetPlace(cursor->GetModelPosition());
	}

	/**************************************
	道を作る
	***************************************/
	void FieldController::BuildRoad()
	{
		using namespace Field::Model;

		//操作対象のプレイスをRoadタイプに変換
		std::vector<PlaceModel*> route = operateContainer->GetPlaces();
		for (auto&& place : route)
		{
			if (place->IsType(PlaceType::None))
				place->SetType(PlaceType::Road);
		}

		//ルートモデル作成
		RouteModelPtr ptr = RouteModel::Create(route);
		routeContainer.push_back(ptr);
	
		//端点設定
		ptr->SetEdge();

		//オブジェクト設定

		//隣接するルートと連結させる
		RouteProcessor::ConnectWithEdge(ptr, routeContainer);
		RouteProcessor::Process(ptr, routeContainer);
	}
}