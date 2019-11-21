//=====================================
//
// ゲームタイトル[GameTitle.cpp]
// 機能：タイtル状態
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GameTitle.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"

//=====================================
// 入場処理
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	//タイトル、選択肢などなど
	// タイトル画面で使用するUIの描画をON

	// 使用しないUIの描画をOFF
	entity.field->SetActive(false);
	entity.gameViewer->SetActive(false);
	entity.guideViewer->SetActive(false);
}

//=====================================
// 更新処理
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
	//今はとりあえず作っただけ
	State next = State::Title;
	return next;
}
