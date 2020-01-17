//=============================================================================
//
// �C�x���g�R���g���[���[�N���X [EventController.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EVENTCONTROLLER_H_
#define _EVENTCONTROLLER_H_

#include "EventBase.h"
#include "../Viewer/GameScene/ParameterContainer/EventViewerParam.h"
#include "../Field/FieldConfig.h"
#include "../Field/FieldEventHandler.h"

#include <map>

//*****************************************************************************
// �O���錾(���[�͂ܒǋL)
//*****************************************************************************
class EventViewer;
class BoardPolygon;
class EventViewerParam;
class EventCamera;
class BeatGameViewer;
class BaseEmitter;

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
	EventCamera *camera;
	BeatGameViewer *beatViewer;

	bool InBanStock;
	bool InPauseEvent;
	//bool IsViewerPlaying;

	std::map<Field::FieldPosition, BaseEmitter*> infoEmitterContainer;

	void LoadCSV(const char* FilePath);

#if _DEBUG
	BoardPolygon *polygon;
	void DrawDebug(void);
#endif

public:
	EventController(int FieldLevel, int csvNo);
	~EventController();

	void Init(int FieldLevel, int csvNo);
	void Init_Tutorial(void);
	void Uninit(void);
	void Update(void);
	void UpdateViewer(void);
	void DrawEventObject(void);
	void DrawEventViewer(void);
	bool CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& route, int FieldLevel);
	void ReceiveFieldEventHandler(FieldEventHandler *Ptr);
	void SetBanStock(bool Flag);
	void SetInPause(bool Flag);
	bool GetInPause(void);
	bool EventDebug(int fieldLevel);
	void ClearEventViewer(void);
	bool IsEmptyEventVec() const;

	friend class PresenDebugController;
};

#endif
