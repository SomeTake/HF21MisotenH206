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

	std::vector <BaseViewer*> eventViewer;

private:
	int eventViewerMax;

	EventTelop * eventTelop;
	EventMessage *eventMessage;
};

#endif

