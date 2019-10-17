//=============================================================================
//
// �C�x���g���N���X [EventBase.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EVENTBASE_H_
#define _EVENTBASE_H_

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventBase
{
protected:
	const char* Message = nullptr;
	int Type = 0;
	int FieldLevel = 0;
	int RemainingTime = 0;
	bool UseFlag = true;

public:
	EventBase(int FieldLevel, int Type);
	~EventBase();
	virtual void Update(void);
	virtual void Draw(void);
	virtual void SetEventViewerMsg(void);
	bool GetUse(void) { return this->UseFlag; };
};

#endif
