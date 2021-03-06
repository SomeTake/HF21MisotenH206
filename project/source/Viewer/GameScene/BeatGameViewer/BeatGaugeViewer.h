//=============================================================================
//
// 連打ゲームゲージビュアー処理 [BeatGaugeViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_GAUGE_VIEWER_H_
#define _BEAT_GAUGE_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <functional>
#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class ViewerAnimater;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatGaugeViewer :public BaseViewer
{
public:
	BeatGaugeViewer();
	~BeatGaugeViewer();

	void Update();
	void Draw(void);
	void Set(float percent);

private:
	BaseViewerDrawer *bar;
	BaseViewerDrawer *frame;
	ViewerAnimater *anim;

	//ゲージバー描画処理
	void DrawBar(void);

	//ゲージパーセント
	float gaugePer;
};
#endif