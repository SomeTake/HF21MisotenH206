//=============================================================================
//
// ストック使用不可イベントクラス [BanStockUseEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "BanStockUseEvent.h"
#include "../MinusEvent/BeatGame.h"
#include "../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"
#include "../../Sound/PlayBGM.h"
#include "../../Booth/BoothController.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// デフォルトの効果時間
const int DefaultDebuffFrame = 300;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
BanStockUseEvent::BanStockUseEvent(EventViewer* eventViewer,
	BeatGameViewer *beatViewer,
	std::function<void(bool)> SetBanStock,
	std::function<bool(void)> GetInPause) :
	EventBase(true),
	RemainTime(DefaultDebuffFrame),
	InDebuff(false),
	SetBanStock(SetBanStock),
	GetInPause(GetInPause),
	eventViewer(eventViewer),
	beatViewer(beatViewer)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
BanStockUseEvent::~BanStockUseEvent()
{
	SAFE_DELETE(beatGame);
	eventViewer = nullptr;
}

//=============================================================================
// 初期化
//=============================================================================
void BanStockUseEvent::Init()
{
	// 連打ゲームインスタンス
	beatGame = new BeatGame(BeatGame::BanStockUse, beatViewer, [&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::AI_Strike, nullptr);

	// 怒り顔エフェクト設置
	GameParticleManager::Instance()->SetAngryFaceEffect();

	// 怒り顔エフェクト終わるまで待つ
	TaskManager::Instance()->CreateDelayedTask(150, [&]() {	
		PlayBGM::Instance()->FadeOut();
		PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::AIBurstEvent, SoundConfig::VolumeBGM, 60, false);
		beatGame->CountdownStart(); 
	});

	SE::Play(SoundConfig::SEID::AIBurstSE, 1.0f);

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void BanStockUseEvent::Update()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	beatGame->Update();

	if (InDebuff && !GetInPause())
	{
		RemainTime--;
		if (RemainTime <= 0)
		{
			// 封印解除
			fieldEventHandler->SealUsingItem(false);
			SetBanStock(false);
			UseFlag = false;
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void BanStockUseEvent::Draw()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	beatGame->Draw();
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string BanStockUseEvent::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// イベント終了処理
//=============================================================================
void BanStockUseEvent::EventOver(void)
{
	// イベント終了、ゲーム続行
	SetBanStock(false);
	fieldEventHandler->ResumeGame();
	UseFlag = false;

	GuideViewer::Instance()->SetData("AIの暴走を食い止めました",
		GuideActor::AnimState::Salute, 
		SoundConfig::AIOutofControllStop);
}

//=============================================================================
// 連打ゲームの結果による処理
//=============================================================================
void BanStockUseEvent::ReceiveBeatResult(bool IsSuccess)
{
	if (IsSuccess)
	{
		//防衛に成功したら全ての町をリンクレベルを+1
		fieldEventHandler->AdjustAllLinkLevel(1);

		// 成功
		EventOver();
	}
	else
	{
		// 失敗、ストック使用封印
		fieldEventHandler->SealUsingItem(true);
		InDebuff = true;
		SetBanStock(true);
		fieldEventHandler->ResumeGame();

		GuideViewer::Instance()->SetData("ドリルが使用不可",
			GuideActor::AnimState::Pain,
			SoundConfig::AIOutofControll);
	}

	PlayBGM::Instance()->FadeOut();
	PlayBGM::Instance()->ResumePrev();
}

