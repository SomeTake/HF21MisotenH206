//=====================================
//
//GamePause.cpp
//機能:ゲーム中断ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GamePause.h"
#include "../../Event/EventController.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"

/**************************************
入場処理
***************************************/
void GameScene::GamePause::OnStart(GameScene & entity)
{
	//NOTE:ここでFieldViewerをオフにしてしまうとレベルアップが見えなくなるのでしない
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GamePause::OnUpdate(GameScene & entity)
{
	//ロジック以外を更新
	entity.field->UpdateObject();

	//ポップアップ終了の待機中はイベントのオブジェクトを更新させない
	if (!entity.field->ShouldWaitPopup())
	{
		//イベント中はFieldViewerをオフに
		//NOTE：汚いけどとりあえずこのやり方でやってしまう
		entity.field->SetViewerActive(false);
		entity.gameViewer->SetActive(false);
		GuideViewer::Instance()->SetActive(false);
		//entity.guideViewer->SetActive(false);

		entity.eventController->Update();
	}

	//イベントビューワ更新
	entity.eventController->UpdateViewer();

	//中断解除はイベントハンドラ側に任せる
	return State::Pause;
}
