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
	const static int fieldTypeMax = 3;
	CountViewerDrawer * num[fieldTypeMax];

public:
	ResultScoreViewer();
	~ResultScoreViewer();

	void Update(void);
	void Draw(void);

	//�p�����[�^���󂯂Ƃ锠
	int parameterBox[fieldTypeMax];
};

#endif