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
#include "../Field/FieldController.h"
//#include "../Field/Place/FieldPlaceModel.h"
#include "../Viewer/GameScene/EventViewer/EventViewer.h"


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventController
{
	struct EventInfo
	{
		int x;
		int z;
		int EventType;
	};

private:
	std::vector<EventInfo> EventCSVData;
	std::vector<EventBase*> EventVec;
	EventViewer *eventViewer;
	Field::FieldController *fieldController;
	//static std::vector<Field::Model::PlaceModel*> *route;
	int FieldLevel;

	void LoadCSV(const char* FilePath);
	//void CheckEventHappen(void);

#if _DEBUG
	void DrawDebug(void);
#endif

public:
	EventController(int FieldLevel);
	~EventController();
	void Update(void);
	void Draw(void);
	void CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& route, int FieldLevel);
	void ReceiveFieldController(Field::FieldController* Ptr);
	//void ReceiveRoute(std::vector<Field::Model::PlaceModel*>& route);
};

#endif
