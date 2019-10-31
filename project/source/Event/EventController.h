//=============================================================================
//
// �C�x���g�R���g���[���[�N���X [EventController.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EVENTCONTROLLER_H_
#define _EVENTCONTROLLER_H_

#include "EventBase.h"
#include "../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../Field/FieldConfig.h"
#include "../Field/FieldEventHandler.h"

//*****************************************************************************
// �O���錾(���[�͂ܒǋL)
//*****************************************************************************
class EventViewer;
class BoardPolygon;
class GameViewerParam;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventController
{
	struct EventInfo
	{
		Field::FieldPosition Pos;
		int EventType;
	};

private:
	std::vector<EventInfo> EventCSVData;
	std::vector<EventBase*> EventVec;
	EventViewer *eventViewer;
	Field::FieldController *fieldController;

	bool InBanStock;
	bool InPause;
	int FieldLevel;

	void LoadCSV(const char* FilePath);

#if _DEBUG
	BoardPolygon *polygon;
	void DrawDebug(void);
#endif

public:
	EventController(int FieldLevel);
	~EventController();
	void Update(void);
	void DrawEventObject(void);
	void DrawEventViewer(void);
	void CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& route, int FieldLevel);
	void ReceiveFieldEventHandler(FieldEventHandler *Ptr);
	void EmbedViewerParam(GameViewerParam& param);
	void SetBanStock(bool Flag);
	void SetInPause(bool Flag);
};

#endif
