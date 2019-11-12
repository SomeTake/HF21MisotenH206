//=============================================================================
//
// �����ŃC�x���g�N���X [CityDestroyEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _CityDestroyEvent_H_
#define _CityDestroyEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BeatGame;
class EventViewer;
class EventActorBase;
class EventCamera;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CityDestroyEvent : public EventBase
{
private:
	D3DXVECTOR3 MeteoritePos;
	D3DXVECTOR3 TownPos;
	D3DXVECTOR3 MoveDirection;
	int EventState;
	const Field::Model::PlaceModel* Target;

	BeatGame *beatGame;
	EventViewer* eventViewer;
	EventActorBase *Meteor;
	EventCamera *camera;

public:
	CityDestroyEvent(EventViewer* eventViewer, EventCamera *camera);
	~CityDestroyEvent();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void MeteorFallStart(void);
	void CountdownStart(void);
	void EventOver(void);
	void ReceiveBeatResult(bool IsSuccess);
};

#endif
