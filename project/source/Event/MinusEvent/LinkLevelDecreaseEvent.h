//=============================================================================
//
// �����N���x�������C�x���g�N���X [LinkLevelDecreaseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _LinkLevelDecreaseEvent_H_
#define _LinkLevelDecreaseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LinkLevelDecreaseEvent : public EventBase
{
private:
public:
	LinkLevelDecreaseEvent();
	~LinkLevelDecreaseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
