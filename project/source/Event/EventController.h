//=============================================================================
//
// �C�x���g�R���g���[���[�N���X [EventController.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EVENTCONTROLLER_H_
#define _EVENTCONTROLLER_H_

#include "EventBase.h"
#include <vector>

//*****************************************************************************
// �N���X��`
//*****************************************************************************

class EventController
{
private:
	struct EventInfo
	{
		int x;
		int z;
		int EventType;
	};

	std::vector<EventInfo> EventCSVData;
	std::vector<EventBase*> EventVec;
	int FieldLevel;

	void LoadCSV(const char* FilePath);

#if _DEBUG
	void DrawDebug(void);
#endif

public:
	EventController(int FieldLevel);
	~EventController();
	void ReceiveEvent(void);
	void Update(void);
	void Draw(void);
};

#endif
