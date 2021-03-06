//=============================================================================
//
// 制限時間回復イベントクラス [TimeRecoveryEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "TimeRecoveryEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int RecoveryFrame = 150;
const std::string TimeRecoveryEvent::message[] = {
	{"宇宙人がタイムマシン持ってた"},
	{"宇宙人「なんかすごいビーム」"},
	{"ミステリーサークルに宇宙人！\nパワースポット誕生！"}
};

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
TimeRecoveryEvent::TimeRecoveryEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetData("制限時間が回復",
		GuideActor::AnimState::FistPump,
		SoundConfig::TimeLimitHeal);
}

//=============================================================================
// デストラクタ
//=============================================================================
TimeRecoveryEvent::~TimeRecoveryEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void TimeRecoveryEvent::Update()
{
	fieldEventHandler->AddRemainTime(RecoveryFrame);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void TimeRecoveryEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string TimeRecoveryEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	int r = rand() % 3;
	MessageContainer.push_back(message[r]);

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
