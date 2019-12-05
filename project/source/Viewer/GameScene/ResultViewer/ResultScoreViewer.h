//=============================================================================
//
// ���ʃX�R�A�r���A�[���� [ResultScoreViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_SCORE_VIEWER_H_
#define _RESULT_SCORE_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultScoreViewer :public BaseViewer
{
private:
	const static int telopMax = 4;
	const static int scoreTelopMax = 3;
	const static int totalScorePlaceTextMax = 3;

	CountViewerDrawer *totalScoreNum[telopMax];
	CountViewerDrawer *rewardNum[telopMax];
	BaseViewerDrawer *bg[telopMax];
	BaseViewerDrawer*fieldText[telopMax];
	BaseViewerDrawer*rewardText[telopMax];
	CountViewerDrawer *scoreNum[scoreTelopMax];
	BaseViewerDrawer*scoreText[scoreTelopMax];

	BaseViewerDrawer*placeText[scoreTelopMax];
	BaseViewerDrawer*totalScorePlaceText[totalScorePlaceTextMax];

	int score[4];
	int completeRewardNum[3];

public:
	ResultScoreViewer();
	~ResultScoreViewer();

	void Update(void);
	void Draw(void);

	//�p�����[�^���󂯂Ƃ锠
	int parameterBox[3];
};

#endif