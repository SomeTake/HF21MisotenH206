//=====================================
//
// �J�E���g�A�b�v�����[�h[CountupReward.h]
// �@�\�F�J�E���g�A�b�v����^�C�v�̃����[�h
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _COUNTUPREWARD_H_
#define _COUNTUPREWARD_H_

#include "Reward.h"

//**************************************
// �N���X��`
//**************************************
class CountupReward :
	public Reward
{
private:
	int data;

public:
	CountupReward(RC::Type type, int maxdata);
	~CountupReward();

	void SetData(int data)override;
	void ResetData()override;
};

#endif
