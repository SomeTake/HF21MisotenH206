//=====================================
//
// RendererEffect.h
// 機能:描画エフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RENDEREREFFECT_H_
#define _RENDEREREFFECT_H_

#include "../../main.h"

#include <vector>

/**************************************
クラス定義
***************************************/
class RendererEffect
{
public:
	RendererEffect() {}
	virtual ~RendererEffect() {}

	//ライト情報設定処理
	static void SetLight(int index, const D3DLIGHT9& light);

	//ビュー、プロジェクション行列設定処理
	static void SetView(const D3DXMATRIX& viewMatrix);
	static void SetProjection(const D3DXMATRIX& projectionMatrix);
	
	//変更反映処理
	void Commit(); 
	virtual void CommitLightAndCamera() = 0;

	//描画開始宣言、描画終了宣言
	void Begin();
	void BeginPass(DWORD pass);
	void EndPass();
	void End();

protected:
	LPD3DXEFFECT effect;

	static std::vector<D3DLIGHT9> lightContainer;
	static D3DXMATRIX mtxView;
	static D3DXMATRIX mtxProjection;
};

#endif