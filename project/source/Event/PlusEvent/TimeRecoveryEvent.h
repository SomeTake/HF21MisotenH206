//=============================================================================
//
// �������ԉ񕜃C�x���g�N���X [TimeRecoveryEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _TimeRecoveryEvent_H_
#define _TimeRecoveryEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TimeRecoveryEvent : public EventBase
{
private:
public:
	TimeRecoveryEvent();
	~TimeRecoveryEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
