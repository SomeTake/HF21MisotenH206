//=====================================
//
// SoundConfig.h
// �@�\:�T�E���h�ݒ�
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SOUNDCONFIG_H_
#define _SOUNDCONFIG_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SoundConfig
{
public:
	// BGM�̒ʂ��ԍ�
	enum BGMID
	{
		Title,
		City,
		World,
		Space,
		DestroyEvent,
		UFOEvent,
		AIBurstEvent,
		Result,

		BGMMax
	};

	// SE�̒ʂ��ԍ�
	enum SEID : int
	{
		// *** Voice ***
		// ***** �C�x���g�֘A�{�C�X *****
		AIBonus,				// AI���x���Ƀ{�[�i�X�i�����C�x���g�j
		AIOutofControll,		// AI�\��
		AIOutofControllStop,	// AI�\���j�~
		AllLinkLevelUp,			// �S�Ă̒��̃����N���x���㏸
		DevelopSpeedUp,			// ���W�x�㏸
		StockRecovery,			// �h�����̃X�g�b�N��
		LinkLevelDown,			// 1�̒��̃����N���x���_�E��
		LinkLevelUp,			// 1�̒��̃����N���x���A�b�v
		MeteorBreakFailed,		// 覐΃C�x���g���s
		MeteorBreakSuccess,		// 覐΃C�x���g����
		NewContinent,			// �V�嗤�o��
		NewStar,				// �V�������o��
		NewTown,				// �V�������a��
		TimeLimitHeal,			// �������ԉ�
		UFOFailed,				// UFO�C�x���g���s
		UFOSuccess,				// UFO�C�x���g����
		Ready,					// ���f�B...
		// ***** �Q�[���i�s�֘A�{�C�X *****
		GameStart,				// �Q�[���X�^�[�g
		FieldLevelUp,			// �t�B�[���h���x���A�b�v
		NextField,				// ���̃t�B�[���h���n�܂�
		NewRecord,				// �X�R�A�X�V
		NewReward,				// �V�����B�����������[�h������
		// ***** �����[�h�֘A�{�C�X *****
		ButtonMashing,			// �{�^���A�ŃC�x���g����N���A
		Destructer,				// �R�j�󁛉�
		Artist,					// �����˂��遛��
		Linker,					// ���̃����N���x�������x�����B
		MinusMaster,			// �}�C�i�X�C�x���g����
		PlusMaster,				// �v���X�C�x���g����
		Pioneer,				// ��������
		MasterAI,				// AI���x�������x���ɓ��B
		MinusComplete,			// �}�C�i�X�C�x���g�R���v���[�g
		PlusComplete,			// �v���X�C�x���g�R���v���[�g

		// *** ME ***
		CreationEventME,
		FieldLevelUpME,
		FinishME,

		// *** SE ***
		Select01,			// ����A���I�_
		Select02,			// ���n�_
		Select03,			// ���n�_�i�h�����j
		MoveCursor,			// �J�[�\���ړ�
		Fall,				// ������
		Beat,				// �A��
		BeatStart,			// �A�ŃQ�[���X�^�[�g
		BeatFinish,			// �A�ŃQ�[���I��
		BeatSuccess,		// �A�ŃQ�[������
		BeatFailed,			// �A�ŃQ�[�����s
		Transition,			// �V�[���`�F���W
		NewTownSE,			// �V�������o��
		NewContinentSE,		// �V�嗤�o��
		NewStarSE,			// �V�������a��
		AIBurstSE,			// AI�\��
		Error,				// �����ɓ��͒u���܂���
		EventHappen,		// �C�x���g����
		TimeStopEventHappen,// ���Ԓ�~�C�x���g����
		Bom,				// ���j
		UFO,				// UFO
		NewField,			// �V�����t�B�[���h�ɑJ��
		TimeUp,				// �������ԏI��
		LinkLevelUpSE,		// �����N���x���㏸
		Morphing,			// ���[�t�B���O
		Clap,				// �����L���O�X�V�����Ƃ�����
		Achieve,			// �Q�[�����Ƀ����[�h���B��m�点��
		UFOFall,			// UFO���~��Ă���
		Cancel,				// �L�����Z��

		SEMax
	};

	//�����t�@�C���̃p�X
	static const char* BGMPath[BGMID::BGMMax];
	static const char* SEPath[SEID::SEMax];

	//�{�C�XSE�̉���
	static const float VolumeVoice;

	//BGM�̉���
	static const float VolumeBGM;

	static BGMID GetBgmID(int fieldLevel);
};

#endif