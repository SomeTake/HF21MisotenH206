//=====================================
//
// タイトルビュアー[TitleViewer.h]
// 機能：タイトル画面UI表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _TITLEVIEWER_H_
#define _TITLEVIEWER_H_

#include "../../../main.h"

class TitleLogo;
class SelectViewer;
class GameScene;
class RewardViewer;

//**************************************
// クラス定義
//**************************************
class TitleViewer
{
private:
	TitleLogo* logo;
	SelectViewer* selectViewer;
	RewardViewer* rewardViewer;

	bool isActive;
	bool isSelect;
	bool isFlash;
	int cntFrame;

public:
	enum MenuID
	{
		StartGame,
		ViewReward,
		QuitGame,
		None
	};

	TitleViewer();
	~TitleViewer();

	void Update();
	void Draw();

	void SetActive(bool flag);

	MenuID GetSelectedMenu();
	void SetRewardViewer();
	bool GetRewardViewer();

	void Reset();
};

#endif
