//=============================================================================
//
// �����x�������C�x���g�N���X [CityLevelDecreaseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _CityLevelDecreaseEvent_H_
#define _CityLevelDecreaseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CityLevelDecreaseEvent : public EventBase
{
private:
public:
	CityLevelDecreaseEvent();
	~CityLevelDecreaseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
