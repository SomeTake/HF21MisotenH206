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
#include "../../../../Framework/Particle/BaseEmitter.h"

class EventViewer;
class PlanetActor;
class EventCamera;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NewTownEvent_Space : public EventBase
{
private:
	EventViewer *eventViewer;
	PlanetActor *PlanetModel;
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 BuildPos;
	const Field::Model::PlaceModel* NewPlanet;
	int EventState;
	int CountFrame;
	std::function<void(void)> EventOverFunc;
	EventCamera *camera;
	BaseEmitter* MoveTailEmitter;
	BaseEmitter* StarDustEmitter;

public:
	NewTownEvent_Space(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera* camera);
	~NewTownEvent_Space();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void FallenStart(void);
	//void EventOver(void);
};

#endif
