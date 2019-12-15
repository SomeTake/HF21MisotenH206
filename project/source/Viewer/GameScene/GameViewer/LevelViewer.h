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
	enum FieldType
	{
		City,
		World,
		Space
	};

	const static int guageMax = 3;

	CircleGauge *circleGuage[guageMax];
	CountViewerDrawer *num;
	CountViewerDrawer *overflowNum;
	BaseViewerDrawer *bg;
	BaseViewerDrawer *text;
	BaseViewerDrawer *plus;
	BaseViewerDrawer *place;

	//�����z�b�s���O����
	void HopNumber(void);

	//�Q�[�W�����Z�b�g
	void SetGaugePer(void);

	//�`��pratioLevel�ݒ�
	void SetDrawingRatioLevel(void);

	//�`��pratioLevel����
	void IncreaseDrawingRatioLevel(void);

	//�`��pratioLevel����
	void DecreaseDrawingRatioLevel(void);

	//�������̌��̃e�N�X�`�����Z�b�g����
	void SetPlaceTex(void);

	//�I�[�o�[�t���[���Ă邩�ǂ�����Ԃ�
	bool IsOverflowed(void);

	//�`��pratioLevel
	float drawingRatioLevel;
};

#endif