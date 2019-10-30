//=============================================================================
//
// �X�g�b�N�g�p�s�C�x���g�N���X [BanStockUseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _BanStockUseEvent_H_
#define _BanStockUseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BeatGame;
class EventViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BanStockUseEvent : public EventBase
{
private:
	// �A�ŃQ�[��
	BeatGame *beatGame;

	int RemainTime;

public:
	BanStockUseEvent(EventViewer* eventViewer);
	~BanStockUseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void ReceiveBeatResult(bool IsSuccess);
	void CountdownStart(void);
	void EventOver(void);
};

#endif
