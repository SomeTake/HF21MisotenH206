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
#include <map>
#include <string>

class Reward;
//**************************************
// �N���X��`
//**************************************
class RewardController :
	public BaseSingleton<RewardController>
{
	friend class BaseSingleton<RewardController>;
public:
	// �����[�h�̎��
	enum Type
	{
		ButtonMashing,	// �{�^���A�ŃC�x���g����N���AOK
		Destructer,		// �R�j�󁛉�OK
		Artist,			// �����˂��遛��OK
		Linker,			// ���̃����N���x�������x�����BOK
		MinusMaster,	// �}�C�i�X�C�x���g����OK
		PlusMaster,		// �v���X�C�x���g����OK
		Pioneer,		// ��������OK
		MasterAI,		// AI���x�������x���ɓ��BOK
		MinusComplete,	// �}�C�i�X�C�x���g�R���v���[�gOK
		PlusComplete,	// �v���X�C�x���g�R���v���[�gOK
		Max
	};

	// �����[�h�̍쐬�A�폜
	void Create(Type type, int maxData);
	void AllDelete();

	// �e�����[�h�̓��B�m�F
	bool CheckAchieved(Type rewardType);
	bool CheckFirstAchieved(Type rewardType);

	// �����[�h���B�҂̖��O���m�F�i�ꕶ�����j
	int GetName(Type rewardType, int alphabetNo);

	// �e�����[�h�̃f�[�^���Z�b�g
	void SetRewardData(Type rewardType, int data);

	// �S�����[�h�̃f�[�^�����Z�b�g
	void ResetAllRewardData();

	// �����[�h���B�m�F�̂��߂̃f�[�^
	static const int MaxData[Max];

private:
	RewardController() {}
	~RewardController() {}

	std::map<Type, Reward*> rewardPool;
};

#endif