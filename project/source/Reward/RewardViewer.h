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
namespace RC = RewardConfig;
//**************************************
// �N���X��`
//**************************************
class RewardViewer
{
private:
	AchieveViewer* achieveViewer;
	bool achieved[RC::Type::Max];

public:
	RewardViewer();
	~RewardViewer();

	void Update();
	void Draw();

	void CheckAchieved();
	void ResetAchieved();
};

#endif
