//=============================================================================
//
// AI���x�������C�x���g�N���X [AILevelDecreaseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _AILevelDecreaseEvent_H_
#define _AILevelDecreaseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class AILevelDecreaseEvent : public EventBase
{
private:
public:
	AILevelDecreaseEvent();
	~AILevelDecreaseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
