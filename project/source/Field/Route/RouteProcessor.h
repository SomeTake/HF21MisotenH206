//=====================================
//
//RouteProcessor.h
//機能:ルートモデルを操作するクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ROUTEPROCESSOE_H_
#define _ROUTEPROCESSOE_H_

#include "../../../main.h"
#include "../Place/PlaceConfig.h"
#include "../../../Framework/Pattern/Delegate.h"

#include <vector>
#include <functional>

namespace Field::Model
{
	/**************************************
	クラス定義
	***************************************/
	class RouteProcessor
	{
	public:
		//コンストラクタ、デストラクタ
		RouteProcessor(std::function<void(const PlaceModel*)>& onChangePlaceType);
		RouteProcessor() {}

		//新しく作ったルートに対して隣接しているルートと連結させて加工する
		void Process(RouteModelPtr& model, RouteContainer& routeContainer, std::vector<PlaceModel*>* ignoreList = NULL);

		//新しく作ったルートを端点で他と連結させる
		void ConnectWithEdge(RouteModelPtr& model, RouteContainer& routeContainer);

		//ルートをしていたプレイスで分割する
		RouteContainer Divide(RouteModelPtr& model, PlaceModel* junction, RouteContainer& routeContainer);

	private:
		//プレイスタイプを変化させた際のデリゲート
		std::function<void(const PlaceModel*)> onChangePlaceType;

		void _Process(RouteModelPtr& model, PlaceModel* place, PlaceModel* target, RouteContainer& routeContainer, RouteContainer& divList);

		void _ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer, PlaceModel *edge);
	};
}

#endif