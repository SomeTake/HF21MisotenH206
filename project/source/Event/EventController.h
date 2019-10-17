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
#include "../Field/Place/FieldPlaceModel.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
struct EventInfo
{
	int x;
	int z;
	int EventType;
};

class EventController
{
private:
	static std::vector<EventInfo> EventCSVData;
	static std::vector<EventBase*> EventVec;
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
	static void CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& route, int FieldLevel);
	//static void ReceiveRoute(std::vector<Field::Model::PlaceModel*>& route);
};

#endif
