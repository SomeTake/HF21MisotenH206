//=============================================================================
//
// ���G�x�㏸�C�x���g�N���X [CongestionUpEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _CongestionUpEvent_H_
#define _CongestionUpEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CongestionUpEvent : public EventBase
{
private:
public:
	CongestionUpEvent();
	~CongestionUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
