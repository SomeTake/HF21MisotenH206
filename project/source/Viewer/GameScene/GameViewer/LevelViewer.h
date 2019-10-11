//=============================================================================
//
// AI���x���r���A�[���� [LevelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LEVEL_VIEWER_H_
#define _LEVEL_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CountViewerDrawer;
class CircleGauge;
class GameViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LevelViewer :public BaseViewer
{
public:
	LevelViewer();
	~LevelViewer();

	void Update(void);
	void Draw(void);

private:
	CircleGauge *circleGuage;
	CountViewerDrawer *num;
	GameViewer *gameViewer;

	void UpdateParam(void);
};

#endif