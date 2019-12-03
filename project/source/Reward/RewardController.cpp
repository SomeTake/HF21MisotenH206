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

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const int RewardController::MaxData[] = {
	3, 20, 15, 15, 10, 20, 250, 10000, 7, 4
};

//=====================================
// �f�[�^�쐬
//=====================================
void RewardController::Create(Type type, int maxData)
{
	if (rewardPool.count(type) == 0)
	{
		if (type == MinusComplete || type == PlusComplete)
		{
			Reward* reward = new StateReward(type, maxData);
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
bool RewardController::CheckAchieved(Type rewardType)
{
	return rewardPool[rewardType]->CheckAchieved();
}

//=====================================
// ���B�m�F
//=====================================
bool RewardController::CheckFirstAchieved(Type rewardType)
{
	return rewardPool[rewardType]->CheckFirstAchieved();
}

//=====================================
// ���O�̎擾�i�ꕶ�����j
//=====================================
int RewardController::GetName(Type rewardType, int alphabetNo)
{
	return rewardPool[rewardType]->GetName(alphabetNo);
}

//=====================================
// �f�[�^�̃Z�b�g
//=====================================
void RewardController::SetRewardData(Type rewardType, int data)
{
	rewardPool[rewardType]->SetData(data);
}

//=====================================
// �f�[�^�̃��Z�b�g
//=====================================
void RewardController::ResetRewardData()
{
	for (auto& reward : rewardPool)
	{
		reward.second->ResetAchieved();
		reward.second->ResetData();
	}
}
