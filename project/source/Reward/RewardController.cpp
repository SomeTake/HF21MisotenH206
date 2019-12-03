//=====================================
//
// �����[�h�R���g���[��[RewardController.h]
// �@�\�F�e�����[�h���R���g���[������N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "RewardController.h"
#include "Reward.h"
#include "CountupReward.h"
#include "StateReward.h"
#include "MaxCheckReward.h"

//=====================================
// �f�[�^�쐬
//=====================================
void RewardController::Create(RC::Type type, int maxData)
{
	if (rewardPool.count(type) == 0)
	{
		if (type == RC::MinusComplete || type == RC::PlusComplete)
		{
			Reward* reward = new StateReward(type, maxData);
			rewardPool.emplace(type, reward);
		}
		else if (type == RC::Linker || type == RC::MasterAI)
		{
			Reward* reward = new MaxCheckReward(type, maxData);
			rewardPool.emplace(type, reward);
		}
		else
		{
			Reward* reward = new CountupReward(type, maxData);
			rewardPool.emplace(type, reward);
		}
	}
	else
	{
		char message[64];
		MessageBox(0, message, "This reward already exists", 0);
	}
}

//=====================================
// �f�[�^�S�폜
//=====================================
void RewardController::AllDelete()
{
	for (auto& reward : rewardPool)
	{
		SAFE_DELETE(reward.second);
	}
	rewardPool.clear();
}

//=====================================
// ���B�m�F
//=====================================
bool RewardController::CheckAchieved(RC::Type rewardType)
{
	return rewardPool[rewardType]->CheckAchieved();
}

//=====================================
// ���B�m�F
//=====================================
bool RewardController::CheckFirstAchieved(RC::Type rewardType)
{
	return rewardPool[rewardType]->CheckFirstAchieved();
}

//=====================================
// ���O�̎擾�i�ꕶ�����j
//=====================================
int RewardController::GetName(RC::Type rewardType, int alphabetNo)
{
	return rewardPool[rewardType]->GetName(alphabetNo);
}

//=====================================
// �f�[�^�̃Z�b�g
//=====================================
void RewardController::SetRewardData(RC::Type rewardType, int data)
{
	rewardPool[rewardType]->SetData(data);
}

//=====================================
// �f�[�^�̃��Z�b�g
//=====================================
void RewardController::ResetAllRewardData()
{
	for (auto& reward : rewardPool)
	{
		reward.second->ResetAchieved();
		reward.second->ResetData();
	}
}
