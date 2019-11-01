//=============================================================================
//
// �C�x���g���N���X [EventBase.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EVENTBASE_H_
#define _EVENTBASE_H_

#include <string>
#include <vector>
#include "../Field/FieldEventHandler.h"
#include "../Field/Place/PlaceConfig.h"

using namespace std;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventBase
{
protected:
	bool UseFlag;
	bool Initialized;
	bool IsPauseEvent;
	static FieldEventHandler *fieldEventHandler;

public:
	EventBase(bool IsPauseEvent);
	virtual ~EventBase();
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual string GetEventMessage(int FieldLevel) = 0;
	bool GetUse(void) { return this->UseFlag; };
	bool GetInitialized(void) { return this->Initialized; };
	bool GetIsPauseEvent(void) { return this->IsPauseEvent; };
	static void ReceiveFieldEventHandler(FieldEventHandler *Ptr);
};

#endif
