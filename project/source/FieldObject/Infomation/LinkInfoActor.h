//=====================================
//
// リンクインフォアクター[LinkInfoActor.h]
// 機能：リンクレベルを表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _LINKINFOACTOR_H_
#define _LINKINFOACTOR_H_

#include "InfoActor.h"
#include "InfoDigit.h"
#include "../../Field/FieldConfig.h"

//**************************************
// クラス定義
//**************************************
class LinkInfoActor :
	public InfoActor
{
private:
	static const int MaxDigit = 2;
	int linkLevel;						// リンクレベル
	int digit[MaxDigit];				// リンクレベルを一桁ごとに分離
	InfoDigit* digitActor[MaxDigit];	// 一桁ごとに表示
	Polygon2D* logo;					// リンクレベルのロゴ表示

	// ビューア内の表示場所、サイズ
	static const D3DXVECTOR3 digitPos[MaxDigit];
	static const D3DXVECTOR3 logoPos;
	static const D3DXVECTOR2 digitSize;
	static const D3DXVECTOR2 logoSize;

	// ビューアの表示場所調整
	static const D3DXVECTOR3 upPos[];

public:
	LinkInfoActor(const D3DXVECTOR3& townPos, const int& townLevel, Field::FieldLevel current);
	~LinkInfoActor();

	// 更新、描画
	void Update()override;
	void Draw()override;

	// レベル変更時使用
	void SetLevel(const int& nextLevel);
	int GetLevel();

};

#endif

