//=============================================================================
//
// �^�C�}�[�r���A�[���� [TimerViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TIMER_VIEWER_H_
#define _TIMER_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;
class GameViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TimerViewer :public BaseViewer
{
public:
	TimerViewer();
	~TimerViewer();

	void Update(void);
	void Draw(void);

private:
	BaseViewerDrawer *bg;
	CountViewerDrawer *num;
	GameViewer *gameViewer;

	void UpdateParam(void);
};

#endif