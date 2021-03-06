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
#include "../../Field/Object/WaterHeightController.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 PassengerActor::ActorScale = Vector3::One;
const D3DXVECTOR3 PassengerActor::InitForward = Vector3::Back;

//=====================================
// コンストラクタ
//=====================================
PassengerActor::PassengerActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
{
	mesh = new MeshContainer();

	// レベルに合わせてモデル読み込み
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("Car", mesh);
		current = Car;
		break;
	case Field::World:
		ResourceManager::Instance()->GetMesh("Train", mesh);
		current = Train;
		break;
	case Field::Space:
		ResourceManager::Instance()->GetMesh("Rocket", mesh);
		current = SpaceShip;
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
	SAFE_DELETE(mesh);
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

	//Shipの場合は水面の高さに合わせる
	if (current == State::Ship)
	{
		D3DXVECTOR3 position = transform->GetPosition();
		position.y = WaterHeightController::GetHeight();
		transform->SetPosition(position);
	}

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// メッシュの切り替え
//=====================================
void PassengerActor::ChangeMesh(const char* nextTag)
{
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

//=====================================
// 現在のメッシュの種類を取得
//=====================================
PassengerActor::State PassengerActor::GetType()
{
	return current;
}

//=====================================
// タグを次のメッシュの種類に変更
//=====================================
void PassengerActor::SetType(PassengerActor::State next)
{
	current = next;
}