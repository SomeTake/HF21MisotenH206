//=============================================================================
//
// �����W�x�{�[�i�X�C�x���g�N���X [BonusEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _BonusEvent_H_
#define _BonusEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BonusEvent : public EventBase
{
private:
public:
	BonusEvent();
	~BonusEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
