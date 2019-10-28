//=============================================================================
//
// ストック使用不可イベントクラス [BanStockUseEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "BanStockUseEvent.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
BanStockUseEvent::BanStockUseEvent(int RemainTime) : RemainTime(RemainTime)
{
	// ストック使用封印
	fieldEventHandler->SealUsingItem(true);
}

//=============================================================================
// デストラクタ
//=============================================================================
BanStockUseEvent::~BanStockUseEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void BanStockUseEvent::Update()
{
	RemainTime--;
	if (RemainTime <= 0)
	{
		// 封印解除
		fieldEventHandler->SealUsingItem(false);
		UseFlag = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void BanStockUseEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string BanStockUseEvent::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}
