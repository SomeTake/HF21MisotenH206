//=====================================
//
// RewardNotifier�N���X[RewardNotifier.h]
// �@�\�F�Q�[���������[�h�B����ʒm����N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _RewardNotifier_H_
#define _RewardNotifier_H_

#include "RewardController.h"

class AchieveViewer;
namespace RC = RewardConfig;
//**************************************
// �N���X��`
//**************************************
class RewardNotifier
{
private:
	AchieveViewer* achieveViewer;
	bool achieved[RC::Type::Max];

public:
	RewardNotifier();
	~RewardNotifier();

	void Update();
	void Draw();

	void CheckAchieved();
	void ResetAchieved();
};

#endif
