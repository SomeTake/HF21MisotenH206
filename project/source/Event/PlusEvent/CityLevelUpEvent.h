//=============================================================================
//
// �����x���㏸�C�x���g�N���X [CityLevelUpEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _CityLevelUpEvent_H_
#define _CityLevelUpEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CityLevelUpEvent : public EventBase
{
private:
public:
	CityLevelUpEvent();
	~CityLevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
