//=============================================================================
//
// �C�x���g�r���A�[�Ǘ����� [EventViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_VIEWER_H_
#define _EVENT_VIEWER_H_

#include <vector>
#include <string>
#include "EventTelop.h"
#include "../../../../Framework/Pattern/Delegate.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class EventTelop;
class EventMessage;
class BaseViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventViewer
{
public:
	EventViewer();
	~EventViewer();

	void Update(void);
	void Draw(void);
	void SetEventMessage(const std::string Message);
	void SetEventTelop(EventTelop::TelopID id, Delegate<void(void)> *onFinish);

private:
	int eventViewerMax;

	std::vector <BaseViewer*> eventViewer;

	EventTelop * eventTelop;
	EventMessage *eventMessage;
};

#endif

