//=====================================
//
//SoundEffect.h
//�@�\:�T�E���h�G�t�F�N�g�Ǘ�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SOUNDEFFECT_H_
#define _SOUNDEFFECT_H_

#include "../../main.h"
#include <dsound.h>
#include <unordered_map>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SE
{
public:
	// SE�̎�ނ��
	enum Type
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
		
		Max
	};
	static const char* path[Type::Max];


	//�T�E���h�ǂݍ��ݏ���
	static void Load(const char* path, int tag);

	//�ǂݍ��񂾃T�E���h���N���A���鏈��
	static void Clear();

	//�Đ�����
	//�{�����[����1.0f ~ 0.0f
	static void Play(int tag, float volume);

	//��~����
	static void Stop(int tag);
	static void Stop();

	//�ĊJ����
	static void Resume(int tag);
	static void Resume();

private:
	//�ǂݍ��񂾃T�E���h�̃R���e�i
	static std::unordered_map<int, LPDIRECTSOUNDBUFFER8> soundContainer;
};
#endif