//=============================================================================
//
// ���S�̃����N���x���㏸�C�x���g�N���X [AllLinkLevelUpEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _AllLinkLevelUpEvent_H_
#define _AllLinkLevelUpEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class AllLinkLevelUpEvent : public EventBase
{
private:
public:
	AllLinkLevelUpEvent();
	~AllLinkLevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
