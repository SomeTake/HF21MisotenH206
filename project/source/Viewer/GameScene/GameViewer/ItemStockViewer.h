//=============================================================================
//
// ストックビュアー処理 [ItemStockViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STOCK_VIEWER_H_
#define _STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class ViewerAnimater;
class CountViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ItemStockViewer :public BaseViewer
{
public:
	ItemStockViewer();
	~ItemStockViewer();

	void Update(void);
	void Draw(void);
	void SetInDrawing(bool Flag) { this->InDrawing = Flag; };

	//パラメータを受けとる箱
	int parameterBox;

private:

	BaseViewerDrawer *icon;
	CountViewerDrawer *num;
	ViewerAnimater *anim;
	bool InDrawing;
};


#endif