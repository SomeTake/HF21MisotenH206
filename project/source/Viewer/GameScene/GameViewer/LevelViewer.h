//=============================================================================
//
// AIレベルビュアー処理 [LevelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LEVEL_VIEWER_H_
#define _LEVEL_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CountViewerDrawer;
class CircleGauge;
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class LevelViewer :public BaseViewer
{
public:
	LevelViewer();
	~LevelViewer();

	void Update(void);
	void Draw(void);

	//AIレベルビュアーの種類
	enum StockViewerType
	{
		LevelAI,
		RatioLevel,
	};

	//AIレベルビュアーの種類数
	static const int typeMax = 4;

	//パラメータを受けとる箱
	float parameterBox[2];

private:
	CircleGauge *circleGuage;
	CountViewerDrawer *num;
	BaseViewerDrawer *bg;

	//アニメーション処理
	void Animate();

	//現在のパラメータ
	int currentParam = 0;

	//１フレーム前のパラメータ
	int lastParam = 0;
};

#endif