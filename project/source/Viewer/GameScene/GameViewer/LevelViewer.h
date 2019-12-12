//=============================================================================
//
// AI���x���r���A�[���� [LevelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LEVEL_VIEWER_H_
#define _LEVEL_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <vector>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CountViewerDrawer;
class CircleGauge;
class BaseViewerDrawer;
class RotateViewerDrawer;

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
	enum LevelViewerType
	{
		LevelAI,
		RatioLevel,
		CurrentFieldLevel,
		Max
	};

	//�p�����[�^���󂯂Ƃ锠
	float parameterBox[Max];

private:

	const static int guageMax = 3;

	CircleGauge *circleGuage[guageMax];
	CountViewerDrawer *num;
	BaseViewerDrawer *bg;
	BaseViewerDrawer *text;
	BaseViewerDrawer *place;

	int currentFieldLevel;

	//�����z�b�s���O����
	void HopNumber(void);

	//�`��pratioLevel�ݒ�
	void SetDrawingRatioLevel(void);

	//�`��pratioLevel����
	void IncreaseDrawingRatioLevel(void);

	//�`��pratioLevel����
	void DecreaseDrawingRatioLevel(void);

	//���݂̃p�����[�^
	int currentParam[Max];

	//�P�t���[���O�̃p�����[�^
	int lastParam[Max];

	//�`��pratioLevel
	float drawingRatioLevel;

	//LevelAI�����������ǂ���
	bool isLevelAI_Increasing;

	//LevelAI�����������ǂ���
	bool isLevelAI_Decreasing;
};

#endif