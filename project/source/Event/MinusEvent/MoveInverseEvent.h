//=============================================================================
//
// ���씽�]�C�x���g�N���X [MoveInverseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _MoveInverseEvent_H_
#define _MoveInverseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class MoveInverseEvent : public EventBase
{
private:
public:
	MoveInverseEvent();
	~MoveInverseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
