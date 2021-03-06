//=============================================================================
//
// ストック使用不可イベントクラス [BanStockUseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BanStockUseEvent_H_
#define _BanStockUseEvent_H_

#include "../EventBase.h"
#include <functional>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BeatGame;
class EventViewer;
class BaseViewerDrawer;
class BeatGameViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BanStockUseEvent : public EventBase
{
private:
	int RemainTime;
	bool InDebuff;
	std::function<void(bool)> SetBanStock;
	std::function<bool(void)> GetInPause;

	// 連打ゲーム
	BeatGame *beatGame;
	EventViewer* eventViewer;
	BeatGameViewer *beatViewer;

public:
	BanStockUseEvent(EventViewer* eventViewer,
		BeatGameViewer *beatViewer,
		std::function<void(bool)> SetBanStock,
		std::function<bool(void)> GetInPause);
	~BanStockUseEvent();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void ReceiveBeatResult(bool IsSuccess);
	void EventOver(void);
};

#endif
