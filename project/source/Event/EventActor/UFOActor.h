//=====================================
//
// �C�x���g�A�N�^�[[UFOActor.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#ifndef _UFOActor_H_
#define _UFOActor_H_

#include "EventActorBase.h"

//**************************************
// �N���X��`
//**************************************
class UFOActor : public EventActorBase
{
private:
	D3DXVECTOR3 BaseHoverPos;
	int FrameCount;
	bool InHoverMotion;

	void HoverMotion(void);							// �z�o�����O�^��

public:
	UFOActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~UFOActor();

	void Update() override;
	void SetHoverMotion(bool Flag);
};

#endif
