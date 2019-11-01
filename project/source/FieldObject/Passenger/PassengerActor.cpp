//=====================================
//
// パッセンジャーアクター[PassengerActor.h]
// 機能：フィールド上を行き来するアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PassengerActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../Field/PlaceActorController.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 PassengerActor::ActorScale = Vector3::One;
const D3DXVECTOR3 PassengerActor::InitForward = Vector3::Back;

//=====================================
// コンストラクタ
//=====================================
PassengerActor::PassengerActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
{
	mesh = MeshContainer::Create();

	// レベルに合わせてモデル読み込み
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("Car", mesh);
		break;
	case FModel::World:
		ResourceManager::Instance()->GetMesh("Train", mesh);
		break;
	case FModel::Space:
		ResourceManager::Instance()->GetMesh("Rocket", mesh);
		break;
	default:
		break;
	}

	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);
}

//=====================================
// デストラクタ
//=====================================
PassengerActor::~PassengerActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// 更新
//=====================================
void PassengerActor::Update()
{
	if (!this->IsActive())
		return;
}

//=====================================
// 描画
//=====================================
void PassengerActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// メッシュの切り替え
//=====================================
void PassengerActor::ChangeMesh(const char* nextTag)
{
	mesh = NULL;
	ResourceManager::Instance()->GetMesh(nextTag, mesh);
}

//=====================================
// 目的地への移動
//=====================================
void PassengerActor::MoveDest(const D3DXVECTOR3 dest, std::function<void(void)> callback)
{
	this->dest = dest;
	D3DXVECTOR3 pos = transform->GetPosition();

	// 向かいたい場所へのベクトル
	D3DXVECTOR3 vec = pos - this->dest;

	// 移動フレーム
	int frame = int(D3DXVec3Length(&vec) / Field::Actor::PlaceActorController::PlacePositionOffset) * 15;

	// 向きを合わせてから移動
	Tween::Turn(*this, vec, 30, OutCubic, Vector3::Up, [=]
	{
		Tween::Move(*this, pos, this->dest, frame, InOutCirc, callback);
	});

}