//=============================================================================
//
// �V������(�s�s���x��)�C�x���g�N���X [NewTownEvent_City.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _NewTownEvent_City_H_
#define _NewTownEvent_City_H_

#include "../../EventBase.h"
#include "../../../Field/Place/FieldPlaceModel.h"

class EventViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NewTownEvent_City : public EventBase
{
private:
	EventViewer *eventViewer;
	const Field::Model::PlaceModel* NewTown;
	std::function<void(void)> EventOverFunc;

public:
	NewTownEvent_City(EventViewer *Ptr, std::function<void(void)> EventOverFunc);
	~NewTownEvent_City();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void CreateNewTown(void);
	//void EventOver(void);
};

#endif
