//=============================================================================
//
// AI���x���㏸�C�x���g�N���X [AILevelUpEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _AILevelUpEvent_H_
#define _AILevelUpEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class AILevelUpEvent : public EventBase
{
private:
public:
	AILevelUpEvent();
	~AILevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
