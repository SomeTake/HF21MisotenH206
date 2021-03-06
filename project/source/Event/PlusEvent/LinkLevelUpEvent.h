//=============================================================================
//
// リンクレベル上昇イベントクラス [LinkLevelUpEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _LinkLevelUpEvent_H_
#define _LinkLevelUpEvent_H_

#include "../EventBase.h"
#include <string>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class LinkLevelUpEvent : public EventBase
{
private:
	static const std::string message[3];

public:
	LinkLevelUpEvent();
	~LinkLevelUpEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
