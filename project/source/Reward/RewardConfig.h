//=====================================
//
// �����[�h�R���t�B�O[RewardConfig.cpp]
// �@�\�F�e�����[�h�֘A�̏��܂Ƃ�
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _REWARDCONFIG_H_
#define _REWARDCONFIG_H_

namespace RewardConfig
{
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

	// �����[�h���B�m�F�̂��߂̃f�[�^
	static const int MaxData[] = {3, 20, 15, 5, 10, 20, 250, 10, 4, 7};
}

#endif
