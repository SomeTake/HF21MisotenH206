//=============================================================================
//
// AIレベル上昇イベントクラス [AILevelUpEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "AILevelUpEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float UpPercent = 0.1f;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
AILevelUpEvent::AILevelUpEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetMessage("AIレベルにボーナスポイントが入りました");
	GuideViewer::Instance()->ChangeAnim(GuideActor::AnimState::FistPump);
	SE::Play(SoundConfig::AIBonus, 1.0);
}

//=============================================================================
// デストラクタ
//=============================================================================
AILevelUpEvent::~AILevelUpEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void AILevelUpEvent::Update()
{
	fieldEventHandler->AdjustLevelAI(UpPercent);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void AILevelUpEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string AILevelUpEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	MessageContainer.push_back("茶柱がたった！");

	if (!MessageContainer.empty())
	{
		int MessageNo = rand() % MessageContainer.size();
		return MessageContainer.at(MessageNo);
	}
	else
	{
		string ErrMsg = "イベントメッセージがありません";
		return ErrMsg;
	}
}
