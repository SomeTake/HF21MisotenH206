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
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 GoalPos;
	D3DXVECTOR3 FallDirection;
	int RemainFrame;
	bool TelopOver;
	bool CountOver;
	const Field::Model::PlaceModel* DestroyTown;

	//�����_
	BaseViewerDrawer *point;
	//������
	CountViewerDrawer *fewNum;
	//������
	CountViewerDrawer *intNum;

#if _DEBUG
	static LPDIRECT3DDEVICE9 Device;
	static LPD3DXMESH SphereMesh;
	static D3DMATERIAL9 Material;
#endif

public:
	CityDestroyEvent(EventViewer* eventViewer);
	~CityDestroyEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	// 覐΂�����܂ł̃J�E���g�_�E��
	void Countdown(void);
};

#endif
