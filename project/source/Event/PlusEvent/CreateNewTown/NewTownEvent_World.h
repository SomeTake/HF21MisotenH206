//=============================================================================
//
// �V������(�����x��)�C�x���g�N���X [NewTownEvent_World.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _NewTownEvent_World_H_
#define _NewTownEvent_World_H_

#include "../../EventBase.h"
#include "../../../Field/Place/FieldPlaceModel.h"

class EventViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NewTownEvent_World : public EventBase
{
private:
	EventViewer *eventViewer;
	const Field::Model::PlaceModel* NewTown;
	std::function<void(void)> EventOverFunc;

public:
	NewTownEvent_World(EventViewer *Ptr, std::function<void(void)> EventOverFunc);
	~NewTownEvent_World();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void CreateNewTown(void);
	//void EventOver(void);
};

#endif
