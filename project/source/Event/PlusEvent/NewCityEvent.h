//=============================================================================
//
// �V�������C�x���g�N���X [NewCityEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _NewCityEvent_H_
#define _NewCityEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NewCityEvent : public EventBase
{
private:
public:
	NewCityEvent();
	~NewCityEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
