//=====================================
//
// Planet�A�N�^�[[PlanetActor.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#ifndef _PlanetActor_H_
#define _PlanetActor_H_

#include "EventActorBase.h"
#include "../../../Framework/Particle/BaseEmitter.h"

//**************************************
// �N���X��`
//**************************************
class PlanetActor : public EventActorBase
{
private:
	BaseEmitter* MoveTailEmitter;

#if _DEBUG
	D3DXVECTOR3 Pos;
	int FrameCount;
	void HoverMotion(void);
#endif

public:
	PlanetActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~PlanetActor();

	void Update() override;
};

#endif
