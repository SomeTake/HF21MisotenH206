//=============================================================================
//
// �X�g�b�N�r���A�[���� [StockViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STOCK_VIEWER_H_
#define _STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class StockViewer :public BaseViewer
{
public:
	StockViewer();
	~StockViewer();

	void Update(void);
	void Draw(void);

	//�X�g�b�N�r���A�[�̎��
	enum StockViewerType
	{
		Bridge,
		Drill,
		Insurance,
		EDF
	};

	//�X�g�b�N�r���A�[�̎�ސ�
	static const int stockViewerMax = 4;

	//�p�����[�^���󂯂Ƃ锠
	int parameterBox[stockViewerMax];

private:
	BaseViewerDrawer *icon[stockViewerMax];
	BaseViewerDrawer *iconBG[stockViewerMax];
	CountViewerDrawer *num[stockViewerMax];
	BaseViewerDrawer *numBG[stockViewerMax];

	//�A�j���[�V����
	void Animate(void);
};


#endif