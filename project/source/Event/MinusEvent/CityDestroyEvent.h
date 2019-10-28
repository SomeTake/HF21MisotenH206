//=============================================================================
//
// �����ŃC�x���g�N���X [CityDestroyEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _CityDestroyEvent_H_
#define _CityDestroyEvent_H_

#include "../EventBase.h"
#include "../../Field/Place/FieldPlaceModel.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BeatGame;
class EventViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CityDestroyEvent : public EventBase
{
private:
	D3DXVECTOR3 MeteoritePos;
	D3DXVECTOR3 MissilePos;
	D3DXVECTOR3 TownPos;
	D3DXVECTOR3 MoveDirection;
	bool BeatGameOver;
	bool EventAvoid;
	bool EffectHappened;
	const Field::Model::PlaceModel* Target;

	// �A�ŃQ�[��
	BeatGame *beatGame;

#if _DEBUG
	static LPD3DXMESH SphereMesh;
	static LPD3DXMESH MissileMesh;
	static D3DMATERIAL9 Material;
#endif

public:
	CityDestroyEvent(EventViewer* eventViewer);
	~CityDestroyEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void EventOver(void);
	void CountdownStart(void);
	void ReceiveBeatResult(bool IsSuccess);
};

#endif
