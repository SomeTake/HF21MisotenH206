//=============================================================================
//
// �V������(�F�����x��)�C�x���g�N���X [NewTownEvent_Space.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _NewTownEvent_Space_H_
#define _NewTownEvent_Space_H_

#include "../../EventBase.h"
#include "../../../Field/Place/FieldPlaceModel.h"

class EventViewer;
class EventActor;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NewTownEvent_Space : public EventBase
{
private:
	EventViewer *eventViewer;
	EventActor *PlanetModel;
	D3DXVECTOR3 PlanetPos;
	D3DXVECTOR3 BuildPos;
	D3DXVECTOR3 MoveDirection;
	const Field::Model::PlaceModel* NewPlanet;
	int EventState;
	std::function<void(void)> EventOverFunc;


public:
	NewTownEvent_Space(EventViewer *Ptr, std::function<void(void)> EventOverFunc);
	~NewTownEvent_Space();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void FallenStart(void);
	//void EventOver(void);
};

#endif
