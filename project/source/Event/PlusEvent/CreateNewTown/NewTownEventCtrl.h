//=============================================================================
//
// �V�������C�x���g�N���X [NewTownEventCtrl.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _NewTownEventCtrl_H_
#define _NewTownEventCtrl_H_

#include "../../EventBase.h"
#include "../../../Field/Place/FieldPlaceModel.h"

class EventViewer;
class EventCamera;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NewTownEventCtrl : public EventBase
{
private:
	EventBase *NewTownEvent;
	EventViewer *eventViewer;
	EventCamera *eventCamera;

public:
	NewTownEventCtrl(EventViewer *Ptr, int FieldLevel, EventCamera *camera);
	~NewTownEventCtrl();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	//void CreateNewTown(void);
	virtual void EventOver(void);
};

#endif
