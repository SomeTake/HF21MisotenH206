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

	//�p�����[�^���󂯂Ƃ锠
	int levelAI_Box;
	float ratioLevelBox;

private:
	CircleGauge *circleGuage;
	CountViewerDrawer *num;
};

#endif