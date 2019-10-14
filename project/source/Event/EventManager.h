//=============================================================================
//
// �C�x���g�}�l�[�W���[�N���X [EventManager.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EventManager_H_
#define _EventManager_H_

#include "EventBase.h"
#include <vector>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventManager
{
private:
	std::vector<EventBase*> EventVec;

public:
	EventManager();
	~EventManager();
	void Update(void);
	void Draw(void);
};

#endif
