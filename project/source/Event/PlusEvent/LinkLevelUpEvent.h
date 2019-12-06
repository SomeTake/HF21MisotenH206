//=============================================================================
//
// �����N���x���㏸�C�x���g�N���X [LinkLevelUpEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _LinkLevelUpEvent_H_
#define _LinkLevelUpEvent_H_

#include "../EventBase.h"
#include <string>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LinkLevelUpEvent : public EventBase
{
private:
	static const std::string message[3];

public:
	LinkLevelUpEvent();
	~LinkLevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
