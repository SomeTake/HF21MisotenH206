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
class EventViewer;
class BaseViewerDrawer;
class CountViewerDrawer;

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
	int RemainFrame;
	bool TelopOver;
	bool CountOver;
	bool UseEDF;
	const Field::Model::PlaceModel* DestroyTown;

	//�����_
	BaseViewerDrawer *point;
	//������
	CountViewerDrawer *fewNum;
	//������
	CountViewerDrawer *intNum;

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
	// 覐΂�����܂ł̃J�E���g�_�E��
	void CountdownStart(void);
	void UseMissile(bool Flag);
};

#endif
