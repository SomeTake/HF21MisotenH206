//=============================================================================
//
// �X�g�b�N�񐔉񕜃C�x���g�N���X [StockRecoveryEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _StockRecoveryEvent_H_
#define _StockRecoveryEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class StockRecoveryEvent : public EventBase
{
private:
public:
	StockRecoveryEvent();
	~StockRecoveryEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
