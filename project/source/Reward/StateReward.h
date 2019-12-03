//=====================================
//
// �X�e�[�g�����[�h[StateReward.h]
// �@�\�F�������̏�Ԃ��m�F����^�C�v�̃����[�h
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _STATEREWARD_H_
#define _STATEREWARD_H_

#include "Reward.h"
#include <vector>

//**************************************
// �N���X��`
//**************************************
class StateReward :
	public Reward
{
private:
	std::vector<int> data;

public:
	StateReward(RewardController::Type type, int maxdata);
	~StateReward();

	void SetData(int data)override;
	void ResetData()override;

};

#endif
