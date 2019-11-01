//=============================================================================
//
// AI���x�������C�x���g�N���X [AILevelDecreaseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _AILevelDecreaseEvent_H_
#define _AILevelDecreaseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BeatGame;
class EventViewer;
class EventActor;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class AILevelDecreaseEvent : public EventBase
{
private:
	D3DXVECTOR3 UFOPos;
	D3DXVECTOR3 TownPos;
	int EventState;
	const Field::Model::PlaceModel* Target;

	BeatGame *beatGame;
	EventViewer* eventViewer;
	EventActor *UFO;

public:
	AILevelDecreaseEvent(EventViewer* eventViewer);
	~AILevelDecreaseEvent();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void UFODebutStart(void);
	void ReceiveBeatResult(bool IsSuccess);
	void CountdownStart(void);
	void EventOver(void);
};

#endif
