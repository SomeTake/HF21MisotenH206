//=============================================================================
//
// ���S�̃����N���x���㏸�C�x���g�N���X [AllLinkLevelUpEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _AllLinkLevelUpEvent_H_
#define _AllLinkLevelUpEvent_H_

#include "../EventBase.h"
#include <string>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class AllLinkLevelUpEvent : public EventBase
{
private:
	static const std::string CityMessage[3];
	static const std::string WorldMessage[3];
	static const std::string SpaceMessage[3];

public:
	AllLinkLevelUpEvent();
	~AllLinkLevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
