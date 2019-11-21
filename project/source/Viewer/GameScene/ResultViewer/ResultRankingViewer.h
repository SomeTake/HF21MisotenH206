//=============================================================================
//
// ���ʃ����L���O�r���A�[���� [ResultRankingViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RANKING_VIEWER_H_
#define _RANKING_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultRankingViewer :public BaseViewer
{
public:
	ResultRankingViewer();
	~ResultRankingViewer();

	void Update(void);
	void Draw(void);

	//�p�����[�^���󂯂Ƃ锠
	float parameterBox;

private:
	CountViewerDrawer *num;
};

#endif