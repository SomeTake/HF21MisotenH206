//=============================================================================
//
// �X�g�b�N�g�p�s�C�x���g�N���X [BanStockUseEvent.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _BanStockUseEvent_H_
#define _BanStockUseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BanStockUseEvent : public EventBase
{
private:
public:
	BanStockUseEvent();
	~BanStockUseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
