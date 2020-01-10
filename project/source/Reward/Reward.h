//=====================================
//
// �����[�h[Reward.h]
// �@�\�F�e�����[�h�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _REWARD_H_
#define _REWARD_H_

#include "../../main.h"
#include <string>
#include "RewardConfig.h"
namespace RC = RewardConfig;
class Name;
//**************************************
// �N���X��`
//**************************************
class Reward
{
public:
	Reward(RC::Type type, int maxdata);
	~Reward();

	// �B���҂̖��O���Z�b�g
	void SetName(const Name& name);

	// �B���҂̖��O���m�F
	Name* GetName();

	// ����̃v���C�ŒB���������`�F�b�N
	bool CheckAchieved();

	// �B���҂����łɂ��邩�`�F�b�N
	bool CheckFirstAchieved();

	//����̃v���C�ŏ��B���������ǂ���
	bool IsAchievedThisTime() const;

	// �B�������Z�b�g
	void ResetAchieved();

	// �f�[�^�̃Z�b�g
	virtual void SetData(int data) = 0;
	
	// �f�[�^�̃��Z�b�g
	virtual void ResetData() = 0;

	// �Z�[�u�f�[�^�̓ǂݍ���
	void LoadData(bool flag);

protected:
	RC::Type type;	// �����[�h�̎��
	bool firstAchieve;				// �ŏ��̓��B�m�F
	bool achieve;					// ���B�m�F
	Name* name;						// �B���҂̖��O

	const int MaxData;
};

#endif
