//=====================================
//
// ガイドアクター[GuideViewer.h]
// 機能：ガイド役キャラクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDEACTOR_H_
#define _GUIDEACTOR_H_

#include "../../../../Framework/Core/GameObject.h"
#include "../../../../Framework/Animation/AnimationManager.h"

class BaseEmitter;

//**************************************
// クラス定義
//**************************************
class GuideActor :
	public GameObject
{
public:
	// アニメーションステート
	enum AnimState
	{
		Idle,
		Cheering,	// 右拳を上げて振る○
		Clapping,	// 拍手○
		Excited,	// 手をわちゃわちゃ顔きょろきょろ○
		FistPump,	// 右手でグッとガッツポーズ○
		Pain,		// 腰に痛みが○
		Waving,		// あ、どうもどうも
		Yeah,		// 両手でグッとガッツポーズ○
		ShakeFist,	// 右手を上げて振る
		Salute,		// 敬礼○
		WaveHand,	// 顔の前で手をふる（いやいやないない、みたいな）
		Defeat,		// 顔を手で覆ってああーって感じ○
		Surprised,	// えぇー！？○
		TalkingTypeA,	// 両手を広げてアピールしながら話す○
		TalkingTypeB,	// 電話してる感じ○
		SecretTalk,		// 内緒話
		FightingIdle,	// ファイティングポーズ
		Rush,			// パンチ連打
		Flying,			// 飛行中

		// 最大数
		AnimMax
	};

	// アニメーション読み込みデータ用構造体
	struct AnimData
	{
		const char* tag;
		float playSpeed;
		float shiftTime;
		float deltaTime;
	};

	GuideActor();
	~GuideActor();

	void Update();
	void Draw();

	void LookAt(const D3DXVECTOR3& pos);

	void ChangeAnim(AnimState next, bool animLoop = false);

	void Move(const D3DXVECTOR3& target, int duration);

	void StartPunsh();
	void EndPunch(bool result);

private:
	AnimationManager* anim;					// アニメーションマネージャ
	BaseEmitter* auraEmitter;				// オーラエミッター
	BaseEmitter* punchEmitter;				// パンチエミッター
	static const AnimData data[AnimMax];	// アニメーション読み込み用データ
	static const char* FileName;			// 読み込むXファイル

	void Debug();
};

#endif

