//=============================================================================
//
// �C�x���g���b�Z�[�W�R���e�i�N���X [EventMessageContainer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EventMessageContainer_H_
#define _EventMessageContainer_H_

#include <vector>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventMessageContainer
{
private:
	//std::vector<const char*> MessageContainer;

public:
	EventMessageContainer();
	~EventMessageContainer();
	static void GetEventMessage(int FieldLevel, int EventType, const char** MessagePtr);
};

#endif
