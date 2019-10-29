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
class BaseViewerDrawer;

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

	//AI���x���r���A�[�̎��
	enum StockViewerType
	{
		LevelAI,
		RatioLevel,
	};

	//AI���x���r���A�[�̎�ސ�
	static const int typeMax = 2;

	//�p�����[�^���󂯂Ƃ锠
	float parameterBox[typeMax];

private:
	CircleGauge *circleGuage;
	CountViewerDrawer *num;
	BaseViewerDrawer *bg;

	//�A�j���[�V��������
	void Animate();
};

#endif