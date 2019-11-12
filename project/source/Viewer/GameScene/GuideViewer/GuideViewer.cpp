//=====================================
//
// ガイドビュアー[GuideViewer.cpp]
// 機能：ガイド役キャラクター表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideViewer.h"

const D3DXVECTOR2 GuideViewer::SubScreenSize = D3DXVECTOR2(240.0f, 360.0f);
const D3DXVECTOR3 GuideViewer::SubScreenPosition = D3DXVECTOR3(0.0f, 720.0f, 0.0f);

//=====================================
// コンストラクタ
//=====================================
GuideViewer::GuideViewer()
{
	// 描画用サブスクリーンの作成
	MakeScreen();
	MakeRenderTarget();

	actor = new GuideActor();
}

//=====================================
// デストラクタ
//=====================================
GuideViewer::~GuideViewer()
{
	SAFE_RELEASE(renderTexture);
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(screenVtx);

	SAFE_DELETE(actor);
}

//=====================================
// 更新
//=====================================
void GuideViewer::Update()
{
	actor->Update();
}

//=====================================
// 描画
//=====================================
void GuideViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット切り替え
	LPDIRECT3DSURFACE9 oldSuf;
	const D3DXCOLOR BackColor = D3DXCOLOR(0.0f, 0.0f, 0.05f, 1.0f);
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BackColor, 1.0f, 0);

	// アクターの描画
	actor->Draw();

	//レンダーターゲット復元
	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	//バックバッファへ描画
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetStreamSource(0, screenVtx, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=====================================
// アクターのアニメーション切り替え
//=====================================
void GuideViewer::ChangeAnim(GuideActor::AnimState next)
{
	actor->ChangeAnim(next);
}

//=====================================
// レンダーターゲットの作成
//=====================================
void GuideViewer::MakeRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーテクスチャ作成
	pDevice->CreateTexture((UINT)SubScreenSize.x,
		(UINT)SubScreenSize.y,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	renderTexture->GetSurfaceLevel(0, &renderSurface);
}

//=====================================
// スクリーンの作成
//=====================================
void GuideViewer::MakeScreen()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&screenVtx,
		0);

	VERTEX_2D *pVtx;
	screenVtx->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(SubScreenPosition.x, SubScreenPosition.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(SubScreenPosition.x + SubScreenSize.x, SubScreenPosition.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(SubScreenPosition.x, SubScreenPosition.y + SubScreenSize.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(SubScreenPosition.x + SubScreenSize.x, SubScreenPosition.y + SubScreenSize.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	screenVtx->Unlock();
}