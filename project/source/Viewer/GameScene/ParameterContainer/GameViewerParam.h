//=============================================================================
//
// ゲームビュアーパラメータ [GameViewerParam.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAME_VIEWER_PARAM_H_
#define _GAME_VIEWER_PARAM_H_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GameViewerParam
{
public:
	//AIレベル
	int levelAI;

	//レベル割合
	float ratioLevel;

	//残り時間
	float remainTime;

	//ストック数
	int stockNum;

	//現在のフィールドレベル
	int currentFieldLevel;
};

#endif