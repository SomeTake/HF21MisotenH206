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

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NewTownEventCtrl : public EventBase
{
private:
	EventBase *NewTownEvent;
	EventViewer *eventViewer;

public:
	NewTownEventCtrl(EventViewer *Ptr, int FieldLevel);
	~NewTownEventCtrl();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	//void CreateNewTown(void);
	void EventOver(void);
};

#endif
