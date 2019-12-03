//=====================================
//
// �}�b�N�X�`�F�b�N�����[�h[MaxCheckReward.h]
// �@�\�F�ő�l�𒴂������m�F����^�C�v�̃����[�h
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _MAXCHECKREWARD_H_
#define _MAXCHECKREWARD_H_

#include "Reward.h"

//**************************************
// �N���X��`
//**************************************
class MaxCheckReward :
	public Reward
{
private:
	int data;
public:
	MaxCheckReward(RewardController::Type type, int maxdata);
	~MaxCheckReward();

	void SetData(int data)override;
	void ResetData()override;

};

#endif
