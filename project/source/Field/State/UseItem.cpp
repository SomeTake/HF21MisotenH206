//=====================================
//
//アイテム使用処理[UseItem.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "UseItem.h"
#include "../Controller/FieldInput.h"
#include "../Place/OperatePlaceContainer.h"
#include "../Place/FieldPlaceContainer.h"
#include "../Object/FieldCursor.h"
#include "../Controller/FieldDevelopper.h"
#include "../../Viewer/GameScene/FieldViewer/OperationExplanationViewer.h"
#include "../PlaceActorController.h"
#include "../Place/FieldPlaceModel.h"

namespace Field
{
	/**************************************
	入場処理
	***************************************/
	void FieldController::UseItemState::OnStart(FieldController & entity)
	{
		//ルートの開始点を取得
		Model::PlaceModel* start = entity.GetPlace();
		bool isSea = entity.placeActController->IsOnSea(start->GetPosition());

		//ルートの開始を試みる
		bool result = entity.operateContainer->BeginDevelop(start, isSea);

		//開始できなかったらIdle状態へ遷移する
		if (!result)
		{
			entity.ChangeState(State::Idle);
		}
	}

	/**************************************
	更新処理
	***************************************/
	FieldController::State FieldController::UseItemState::OnUpdate(FieldController & entity)
	{
		//次のステート
		State next = State::Develop;

		//カーソル位置のプレイスを操作対象として追加
		Model::PlaceModel* place = entity.GetPlace();
		bool isSea = entity.placeActController->IsOnSea(place->GetPosition());
		entity.operateContainer->AddDevelop(place, isSea);

		//操作説明を更新
		entity.operationZ = OperationExplanationViewer::OperationID::Z_Cancel;

		entity.operationX = entity.enableDevelop ?
			OperationExplanationViewer::OperationID::X_Develop :
			OperationExplanationViewer::OperationID::X_None;

		//Xキーが押されたら操作対象のプレイスを道に変える
		//TODO：キーボード以外の入力にも対応
		if (entity.input->GetDevelopTrigger())
		{
			if (entity.operateContainer->EndDevelop())
			{
				PlaceVector vector = entity.operateContainer->GetPlaces();
				entity.developper->DevelopPlace(vector, vector.begin());
				entity.operateContainer->Clear();

				next = State::Idle;
			}
		}

		//Zキーが押されたらIdleステートへ遷移
		if (entity.input->GetDevelopCancel())
		{
			entity.operateContainer->Clear();
			next = State::Idle;
		}

		return next;
	}
}