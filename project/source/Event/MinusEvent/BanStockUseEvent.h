//=============================================================================
//
// �X�g�b�N�g�p�s�C�x���g�N���X [BanStockUseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _BanStockUseEvent_H_
#define _BanStockUseEvent_H_

#include "../EventBase.h"
#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BeatGame;
class EventViewer;
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BanStockUseEvent : public EventBase
{
private:
	int RemainTime;
	bool InDebuff;
	std::function<void(bool)> SetBanStock;

	// �A�ŃQ�[��
	BeatGame *beatGame;
	BaseViewerDrawer *Viewer;


public:
	BanStockUseEvent(EventViewer* eventViewer, std::function<void(bool)> SetBanStock);
	~BanStockUseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void ReceiveBeatResult(bool IsSuccess);
	void CountdownStart(void);
	void EventOver(void);
};

#endif
