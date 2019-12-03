//=====================================
//
// �����[�h�R���g���[��[RewardController.h]
// �@�\�F�e�����[�h���R���g���[������N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _REWARDCONTROLLER_H_
#define _REWARDCONTROLLER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"
#include "RewardConfig.h"
#include <map>
#include <string>

class Reward;
namespace RC = RewardConfig;

//**************************************
// �N���X��`
//**************************************
class RewardController :
	public BaseSingleton<RewardController>
{
	friend class BaseSingleton<RewardController>;
public:
	// �����[�h�̍쐬�A�폜
	void Create(RC::Type type, int maxData);
	void AllDelete();

	// �e�����[�h�̓��B�m�F
	bool CheckAchieved(RC::Type rewardType);
	bool CheckFirstAchieved(RC::Type rewardType);

	// �����[�h���B�҂̖��O���m�F�i�ꕶ�����j
	int GetName(RC::Type rewardType, int alphabetNo);

	// �e�����[�h�̃f�[�^���Z�b�g
	void SetRewardData(RC::Type rewardType, int data);

	// �S�����[�h�̃f�[�^�����Z�b�g
	void ResetAllRewardData();

private:
	RewardController() {}
	~RewardController() {}

	std::map<RC::Type, Reward*> rewardPool;
};

#endif