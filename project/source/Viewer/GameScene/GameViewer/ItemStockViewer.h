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
	void InitBanIcon(void);

	//パラメータを受けとる箱
	int parameterBox;
	bool InBanStock;
	bool BanIconDebut;
	bool InPauseEvent;

private:
	BaseViewerDrawer *icon;				// ストックアイコン
	BaseViewerDrawer *BanIcon;			// バツアイコン
	BaseViewerDrawer *BanIcon_White;	// バツアイコン(白)
	CountViewerDrawer *num;

	//アニメーション
	void Animate(void);
	void SetBanIconVertex(float Percent);
	void SetBanIconTexture(float Percent);
};


#endif