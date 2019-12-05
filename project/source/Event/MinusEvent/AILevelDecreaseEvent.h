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
class UFOActor;
class EventCamera;
class BeatGameViewer;
class GuideActor;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class AILevelDecreaseEvent : public EventBase
{
private:
	D3DXVECTOR3 UFOPos;
	D3DXVECTOR3 TownPos;
	int EventState;
	int FrameCount;
	const Field::Model::PlaceModel* Target;

	BeatGame *beatGame;
	EventViewer* eventViewer;
	UFOActor *UFO;
	EventCamera *camera;
	BeatGameViewer *beatViewer;
	GuideActor* guideActor;
	bool success;					// SE�Đ��Ȃǂ̂��߂̐����ۃt���O

public:
	AILevelDecreaseEvent(EventViewer* eventViewer, EventCamera* camera, BeatGameViewer *beatViewer);
	~AILevelDecreaseEvent();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void UFODebutStart(void);
	void ReceiveBeatResult(bool IsSuccess);
	void CountdownStart(void);
	void EventOver(void);

	void OnFinishBeat(bool result);
	void OnFinishEffect();
};

#endif
