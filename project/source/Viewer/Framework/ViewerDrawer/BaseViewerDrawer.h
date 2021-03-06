//=============================================================================
//
// 基底ビュアー描画用処理 [BaseViewerDrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BASE_VIEWER_DRAWER_H_
#define _BASE_VIEWER_DRAWER_H_

#include"../../../../main.h"
#include <string>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// 色定義
#define SET_COLOR_NOT_COLORED	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define SET_COLOR_BLACK			(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define SET_COLOR_RED			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define SET_COLOR_GREEN			(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define SET_COLOR_BLUE			(D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))
#define SET_COLOR_YELLOW		(D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define SET_COLOR_PINK			(D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))
#define SET_COLOR_RIGHTBLUE		(D3DXCOLOR(0.0f,1.0f,1.0f,1.0f))
#define SET_COLOR_ORANGE		(D3DXCOLOR(1.0f,0.4f,0.0f,1.0f))

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BaseViewerDrawer
{
public:
	LPDIRECT3DTEXTURE9 texture;
	VERTEX_2D vertexWk[NUM_VERTEX];
	D3DXVECTOR3	position;
	D3DXVECTOR3	rotation;
	D3DXVECTOR3	size;

	void LoadTexture(const char *path);
	void Draw();
	void SetAlpha(float alpha);
	void SetColor(D3DXCOLOR color);

	virtual void MakeVertex();
	virtual void SetVertexPos();
	virtual void SetTexture(int divX, int divY, int pattern);

	void SetPosition(const D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosition(void);
	D3DXCOLOR GetColor(void);

	BaseViewerDrawer(D3DXVECTOR2 position, D3DXVECTOR2 size, const char* path);
	BaseViewerDrawer();
	virtual ~BaseViewerDrawer();
};

#endif