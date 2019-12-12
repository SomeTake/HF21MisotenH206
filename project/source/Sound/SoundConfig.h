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

	// Voice�̒ʂ��ԍ�
	enum VoiceID
	{
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

		VoiceMax
	};

	//�����t�@�C���̃p�X
	static const char* BGMPath[BGMID::BGMMax];
	static const char* VoicePath[VoiceID::VoiceMax];

	//�{�C�XSE�̉���
	static const float VolumeVoice;
};

#endif