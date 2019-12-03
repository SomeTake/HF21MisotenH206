//=====================================
//
// �����[�h�r���A�[[RewardViewer.h]
// �@�\�F�e�����[�h��\������N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _REWARDVIEWER_H_
#define _REWARDVIEWER_H_

#include "RewardController.h"

class AchieveViewer;
//**************************************
// �N���X��`
//**************************************
class RewardViewer
{
private:
	AchieveViewer* achieveViewer;
	bool achieved[RewardController::Type::Max];

public:
	RewardViewer();
	~RewardViewer();

	void Update();
	void Draw();

	void CheckAchieved();
	void ResetAchieved();
};

#endif
