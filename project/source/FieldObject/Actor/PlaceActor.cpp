//=====================================
//
// プレイスアクター[PlaceActor.cpp]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlaceActor.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../Animation/ActorAnimation.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 PlaceActor::ActorScale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// コンストラクタ
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel) 
{
	// メッシュコンテナの作成
	mesh = MeshContainer::Create();

	// ステータスセット
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);
}

//=====================================
// デストラクタ
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// 更新
//=====================================
void PlaceActor::Update()
{

#if _DEBUG
	Debug();
#endif
}

//=====================================
// 描画
//=====================================
void PlaceActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y軸回転
//=====================================
void PlaceActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// メッシュデータのカラー変更
//=====================================
void PlaceActor::SetColor(const D3DXCOLOR& color, UINT index)
{
	mesh->SetMaterialColor(color, index);
}

//=====================================
// デバッグ
//=====================================
void PlaceActor::Debug()
{
	Debug::Begin("PlaceActor", false);
	Debug::Text("ChangeAnimation");
	Debug::NewLine();
	if (Debug::Button("Fall"))
	{
		ActorAnimation::Fall(*this);
	}
	Debug::NewLine();
	if (Debug::Button("RotateAndExpantion"))
	{
		ActorAnimation::RotateAndExpantion(*this);
	}
	Debug::NewLine();
	if (Debug::Button("RotateAndShrink"))
	{
		ActorAnimation::RotateAndShrink(*this);
	}
	Debug::NewLine();
	if (Debug::Button("ExpantionYAndReturnToOrigin"))
	{
		ActorAnimation::ExpantionYAndReturnToOrigin(*this);
	}
	Debug::NewLine();
	if (Debug::Button("ResetScale"))
	{
		transform->SetScale(ActorScale);
	}
	Debug::NewLine();
	Debug::End();
}