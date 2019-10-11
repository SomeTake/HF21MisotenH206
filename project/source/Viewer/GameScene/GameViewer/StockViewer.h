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

	enum StockViewerType
	{
		Bridge,
		Drill,
		Insurance,
		EDF
	};

	static const int stockViewerMax = 4;

	//�p�����[�^���󂯂Ƃ锠
	int parameterBox[stockViewerMax];

private:
	BaseViewerDrawer * icon[stockViewerMax];
	BaseViewerDrawer *iconBG[stockViewerMax];
	BaseViewerDrawer *numBG[stockViewerMax];
	CountViewerDrawer *num[stockViewerMax];

	void Animate(void);

	//�r���A�[�̕\���Ԋu
	const float intervalViewerPos = 185.0f;

	//�A�C�e���A�C�R���e�N�X�`���p�X
	const char *iconTexPath[stockViewerMax]
	{
		"data/TEXTURE/Viewer/GameViewer/StockViewer/Bridge/BridgeIcon.png",
		"data/TEXTURE/Viewer/GameViewer/StockViewer/Drill/DrillIcon.png",
		"data/TEXTURE/Viewer/GameViewer/StockViewer/Insurance/InsuranceIcon.png",
		"data/TEXTURE/Viewer/GameViewer/StockViewer/EDF/EDF_Icon.png",
	};

	const float hopNumValue = 30.0f;
	const D3DXVECTOR3 initNumSize = D3DXVECTOR3(7.50f, 15.0f, 0.0f);
};


#endif