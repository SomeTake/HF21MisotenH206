//=============================================================================
//
// �L���l�C�x���g�N���X [FamousPeopleEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _FamousPeopleEvent_H_
#define _FamousPeopleEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FamousPeopleEvent : public EventBase
{
private:
public:
	FamousPeopleEvent();
	~FamousPeopleEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
