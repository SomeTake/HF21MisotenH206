//=============================================================================
//
// カウントビュアー描画用処理 [CountViewerDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include"../../../../main.h"
#include "CountViewerDrawer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CountViewerDrawer::CountViewerDrawer(D3DXVECTOR2 position, D3DXVECTOR2 size, const char* path, 
	float intervalPosScr, float intervalPosTex, int placeMax)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->size.x = size.x;
	this->size.y = size.y;

	this->intervalPosScr = intervalPosScr;
	this->intervalPosTex = intervalPosTex;
	this->placeMax = placeMax;

	LoadTexture(path);
	MakeVertex();
}

//=============================================================================
// コンストラクタ
//=============================================================================
CountViewerDrawer::CountViewerDrawer()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CountViewerDrawer::~CountViewerDrawer()
{
}

//=============================================================================
// 頂点座標の設定　（カウンター専用）
//=============================================================================
void CountViewerDrawer::SetVertexPos(int placeCount, float placeInterval)
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(position.x - placeCount * placeInterval, position.y, 0.0f) 
		+ D3DXVECTOR3(-size.x/2, -size.y/2, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(position.x - placeCount * placeInterval, position.y, 0.0f) 
		+ D3DXVECTOR3(size.x/2, -size.y/2, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(position.x - placeCount * placeInterval, position.y, 0.0f) 
		+ D3DXVECTOR3(-size.x/2, size.y/2, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(position.x - placeCount * placeInterval, position.y, 0.0f) 
		+ D3DXVECTOR3(size.x/2, size.y/2, 0.0f);
}

//=============================================================================
//オブジェクトのテクスチャ座標設定処理　（カウンター専用）
//=============================================================================
void CountViewerDrawer::SetTexture(int number, float placeInterval)
{
	// 頂点座標の設定
	float sizeX = 1.0f / texDivX;
	float sizeY = 1.0f / texDivY;
	int x = number % texDivX;
	int y = number / texDivX;

	vertexWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vertexWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vertexWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vertexWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

//=============================================================================
//0を表示するカウンター描画処理（引数注意）
//=============================================================================
void CountViewerDrawer::DrawCounter(int baseNumber, int parameterBox, int placeMax,
	float intervalNumberScr, float intervalNumberTex)
{
	int value = parameterBox;

	for (int nCntPlace = 0; nCntPlace < placeMax; nCntPlace++)
	{
		int num = 0;
		num = value % baseNumber;
		value /= baseNumber;

		this->SetVertexPos(nCntPlace, intervalNumberScr);
		SetTexture(num, intervalNumberTex);
		this->Draw();
	}
}

//=============================================================================
//0を表示しないカウンター描画処理（引数注意)
//=============================================================================
void CountViewerDrawer::DrawCounter(int baseNumber, int parameterBox,
	float intervalNumberScr, float intervalNumberTex)
{
	int placeMax = (parameterBox == 0) ? 1 : (int)log10f((float)parameterBox) + 1;
	int value = parameterBox;

	for (int nCntPlace = 0; nCntPlace < placeMax; nCntPlace++)
	{
		int num = 0;
		num = value % baseNumber;
		value /= baseNumber;

		this->SetVertexPos(nCntPlace, intervalNumberScr);
		SetTexture(num, intervalNumberTex);
		this->Draw();
	}
}

//=============================================================================
// 数字ホッピング処理
//=============================================================================
float CountViewerDrawer::HopNumber(float sizeY, float initSizeY, float hopValue)
{
	if (isHopped == true)
	{
		sizeY = initSizeY + (hopValue * sinf(radian));
		if (radian >= D3DX_PI)
		{
			radian = 0.0f;
			isHopped = false;
		}
		radian += hopSpeed;
	}

	return sizeY;
}

//=============================================================================
// 描画処理
//=============================================================================
void CountViewerDrawer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}
