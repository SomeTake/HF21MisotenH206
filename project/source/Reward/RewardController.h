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
#include <vector>

class Reward;
class Name;
namespace RC = RewardConfig;

//**************************************
// �N���X��`
//**************************************
class RewardController :
	public BaseSingleton<RewardController>
{
	friend class BaseSingleton<RewardController>;
public:
	// **************�J�n�A�I����*****************************
	// �����[�h�̍쐬�A�폜
	void Create();
	void AllDelete();

	// **************�Q�[���i�s��******************************
	// �e�����[�h�̃f�[�^���Z�b�g
	void SetRewardData(RC::Type rewardType, int data);

	// �e�����[�h�̓��B�m�F
	bool IsAchieved(RC::Type type);

	// **************���U���g��ʗp****************************
	// �S�����[�h�̓��B�m�F�i�B�����������[�h��ENUM��S�ė񋓂��ĕԂ��j
	std::vector<RC::Type> IsAllAchieved();

	// �S�����[�h�Ȃ�����ǂꂩ�ЂƂł����B���̂��̂����邩
	bool FindFirstAchieved();

	// ����̃v���C�ŒB�����������[�h��S�ĒB���ς݂ɂ���i���U���g�I�����j
	void SetFirstAchieved(const Name& name);

	// **************�����[�h�m�F��ʗp************************
	// ���ɓ��B�҂����邩�ifalse�Ȃ疢�B���j
	bool IsFirstAchieved(RC::Type rewardType);

	// �����[�h���B�҂̖��O���m�F
	Name* GetName(RC::Type rewardType);

	// **************�Q�[������************************
	// �S�����[�h�̃f�[�^�����Z�b�g
	void ResetAllRewardData();

private:
	RewardController() {}
	~RewardController() {}

	std::map<RC::Type, Reward*> rewardPool;
};

#endif