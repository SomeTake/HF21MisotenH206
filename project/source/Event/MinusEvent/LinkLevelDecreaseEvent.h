//=============================================================================
//
// �����N���x�������C�x���g�N���X [LinkLevelDecreaseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _LinkLevelDecreaseEvent_H_
#define _LinkLevelDecreaseEvent_H_

#include "../EventBase.h"
#include <string>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LinkLevelDecreaseEvent : public EventBase
{
private:
	static const std::string CityMessage[3];
	static const std::string WorldMessage[3];
	static const std::string SpaceMessage[3];

public:
	LinkLevelDecreaseEvent();
	~LinkLevelDecreaseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
