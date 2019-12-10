//=============================================================================
//
// ���ʃX�R�A�r���A�[���� [ResultScoreViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_SCORE_VIEWER_H_
#define _RESULT_SCORE_VIEWER_H_

#include <functional>
#include "../../../../main.h"
#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class ViewerAnimater;
class TextViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultScoreViewer :public BaseViewer
{
private:
	enum AnimLayer
	{
		TelopIn,
		TelopOut,
		Max
	};
	const static int telopMax = 4;

	BaseViewerDrawer *bg[telopMax];
	BaseViewerDrawer*fieldText[telopMax];
	TextViewer *scoreText[telopMax];
	TextViewer *rewardText[telopMax];
	ViewerAnimater*anim[Max];

	int score[telopMax];
	int completeRewardNum[telopMax];

	//�e���b�v�X�N���[���C��
	void InCityTelop();
	void InWorldTelop();
	void InSpaceTelop();
	void InResultTelop();

	//�e���b�v�X�N���[���A�E�g
	void OutCityTelop();
	void OutWorldTelop();
	void OutSpaceTelop();
	void OutResultTelop();

	//�~�܂������W
	D3DXVECTOR2 bgStopPos[telopMax];
	D3DXVECTOR2 fieldTextStopPos[telopMax];

	void GetStopPos();
	void SetText();

	bool isInPlaying;
	bool isOutPlaying;

	std::function<void()> CallbackInFin = nullptr;
public:
	ResultScoreViewer();
	~ResultScoreViewer();

	void Update(void);
	void Draw(void);

	void SetTelopIn(std::function<void()> CallbackInFin);
	void SetTelopOut();

	//�p�����[�^���󂯂Ƃ锠
	int parameterBox[3];
};

#endif