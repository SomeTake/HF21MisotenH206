//=============================================================================
//
// �����ŃC�x���g�N���X [CityDestroyEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _CityDestroyEvent_H_
#define _CityDestroyEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CityDestroyEvent : public EventBase
{
private:
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 GoalPos;
	D3DXVECTOR3 FallDirection;
	static LPDIRECT3DDEVICE9 Device;
	static LPD3DXMESH SphereMesh;
	static D3DMATERIAL9 Material;

public:
	CityDestroyEvent(int FieldLevel, D3DXVECTOR3 GoalPos);
	~CityDestroyEvent();
	void Update(void) override;
	void Draw(void) override;
	std::string GetEventMessage(int FieldLevel) override;
};

#endif
