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
		ButtonMashing,	// �{�^���A�ŃC�x���g����N���A
		Destructer,		// �R�j�󁛉�
		Artist,			// �����˂��遛��
		Linker,			// ���̃����N���x�������x�����B
		MinusMaster,	// �}�C�i�X�C�x���g����
		PlusMaster,		// �v���X�C�x���g����
		Pioneer,		// ��������
		MasterAI,		// AI���x�������x���ɓ��B
		MinusComplete,	// �}�C�i�X�C�x���g�R���v���[�g
		PlusComplete,	// �v���X�C�x���g�R���v���[�g
		Max
	};

	// �����[�h���B�m�F�̂��߂̃f�[�^
	static const int MaxData[] = {3, 20, 15, 15, 10, 20, 250, 10000, 4, 7};
}

#endif
