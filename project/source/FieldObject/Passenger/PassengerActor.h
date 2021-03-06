//=====================================
//
// パッセンジャーアクター[PassengerActor.h]
// 機能：フィールド上を行き来するアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PASSENGERACTOR_H_
#define _PASSENGERACTOR_H_

#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../Field/Place/PlaceConfig.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../Field/FieldConfig.h"

#include <functional>

//**************************************
// 列挙子設定
//**************************************
namespace FModel = Field::Model;

//**************************************
// クラス定義
//**************************************
class PassengerActor :
	public GameObject
{
	friend class Tween;
public:
	PassengerActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~PassengerActor();

	virtual void Update();
	void Draw();

	// メッシュの状態を表すステート
	enum State
	{
		Car,
		Ship,
		Train,
		SpaceShip,
	};

	State GetType();						// 現在のメッシュの状態を取得
	void SetType(State next);				// 次のメッシュの状態にタグをセット
	void ChangeMesh(const char* nextTag);	// メッシュ切り替え
	void MoveDest(const D3DXVECTOR3 dest, std::function<void(void)> callback = nullptr);	// 目的地までの移動(到達したらcallbackを返す)

private:
	State current;			// 現在のメッシュの状態

	MeshContainer* mesh;
	D3DXVECTOR3 dest;		// 目的地

	// 定数定義
	static const D3DXVECTOR3 ActorScale;
	static const D3DXVECTOR3 InitForward;
};

#endif
