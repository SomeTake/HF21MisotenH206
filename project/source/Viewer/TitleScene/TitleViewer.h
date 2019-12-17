//=====================================
//
// �^�C�g���r���A�[[TitleViewer.h]
// �@�\�F�^�C�g�����UI�\��
// Author:GP12B332 19 ���J���u
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
// �N���X��`
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

	void Reset();
};

#endif
