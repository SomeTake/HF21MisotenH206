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
#include <algorithm>
#include "../../Framework/Core/PlayerPrefs.h"
#include "../../Framework/Core/Utility.h"
#include "../Viewer/NameViewer/Name.h"

//=====================================
// �f�[�^�쐬
//=====================================
void RewardController::Create()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		RC::Type type = RC::Type(i);
		if (rewardPool.count(type) == 0)
		{
			if (type == RC::MinusComplete || type == RC::PlusComplete)
			{
				Reward* reward = new StateReward(type, RC::MaxData[i]);
				rewardPool.emplace(type, reward);
			}
			else if (type == RC::Linker || type == RC::MasterAI)
			{
				Reward* reward = new MaxCheckReward(type, RC::MaxData[i]);
				rewardPool.emplace(type, reward);
			}
			else
			{
				Reward* reward = new CountupReward(type, RC::MaxData[i]);
				rewardPool.emplace(type, reward);
			}

			// �Z�[�u�f�[�^�̓ǂݍ���
			bool flag = PlayerPrefs::GetBool(Utility::ToString(type));
			rewardPool[type]->LoadData(flag);
			if (flag)
			{
				int num[3];
				for (int n = 0; n < 3; n++)
				{
					num[n] = PlayerPrefs::GetNumber<int>(Utility::ToString(type) + std::to_string(n));
				}
				rewardPool[type]->SetName(Name(num[0], num[1], num[2]));
			}
		}
		else
		{
			char message[64];
			MessageBox(0, message, "This reward already exists", 0);
		}
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
std::vector<RC::Type> RewardController::GetAllAchieved()
{
	std::vector<RC::Type> ret;

	for (int i = 0; i < RC::Type::Max; i++)
	{
		if (rewardPool[RC::Type(i)]->CheckAchieved())
		{
			ret.push_back(RC::Type(i));
		}
	}

	return ret;
}

//=====================================
// ���B�m�F
//=====================================
bool RewardController::ExistFirstAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		if (rewardPool[RC::Type(i)]->IsAchievedThisTime())
			return true;
	}
	return false;

	/*auto itr = std::find_if(rewardPool.begin(), rewardPool.end(), [](std::pair<RC::Type, Reward*> a) {
		return a.second->CheckFirstAchieved(); 
	});

	if (itr == rewardPool.end())
	{
		return false;
	}
	else
	{
		return true;
	}*/
}

//=====================================
// ���B�m�F
//=====================================
bool RewardController::IsAchieved(RC::Type type)
{
	return rewardPool[type]->CheckAchieved();
}

//=====================================
// ���B�m�F
//=====================================
bool RewardController::IsFirstAchieved(RC::Type rewardType)
{
	return rewardPool[rewardType]->CheckFirstAchieved();
}

//=====================================
// ���B���҂̖��O���Z�b�g
//=====================================
void RewardController::SetFirstAchieverName(const Name& name)
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		RewardConfig::Type key = RewardConfig::Type(i);

		if (rewardPool[key]->IsAchievedThisTime())
		{
			rewardPool[key]->SetName(name);

			// �Z�[�u�f�[�^�X�V
			PlayerPrefs::SaveBool(Utility::ToString(key), true);
			for (int num = 0; num < 3; num++)
			{
				PlayerPrefs::SaveNumber(Utility::ToString(key) + std::to_string(num), rewardPool[key]->GetName()->Get(num));
			}
		}
	}
}

//=====================================
// ���O�̎擾
//=====================================
Name* RewardController::GetName(RC::Type rewardType)
{
	return rewardPool[rewardType]->GetName();
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
