//=====================================
//
// �����[�h[Reward.h]
// �@�\�F�e�����[�h�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _REWARD_H_
#define _REWARD_H_

#include "RewardController.h"
#include <string>

namespace RC = RewardConfig;
//**************************************
// �N���X��`
//**************************************
class Reward
{
public:
	Reward(RC::Type type, int maxdata);
	~Reward();

	// �B���҂̖��O���Z�b�g
	void SetName(int BuffNo, int AlphabetNo);

	// �B���҂̖��O���m�F
	int GetName(int BuffNo);

	// ����̃v���C�ŒB���������`�F�b�N
	bool CheckAchieved();

	// �B���҂����łɂ��邩�`�F�b�N
	bool CheckFirstAchieved();

	// �B�������Z�b�g
	void ResetAchieved();

	// �f�[�^�̃Z�b�g
	virtual void SetData(int data) = 0;
	
	// �f�[�^�̃��Z�b�g
	virtual void ResetData() = 0;

protected:
	RC::Type type;	// �����[�h�̎��
	bool firstAchieve;				// �ŏ��̓��B�m�F
	bool achieve;					// ���B�m�F
	int name[3];					// �B���҂̖��O

	const int MaxData;
};

#endif
