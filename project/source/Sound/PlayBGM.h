//=====================================
//
// �v���CBGM[PlayBGM.h]
// �@�\�FBGM�Đ��p�N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PLAYBGM_H_
#define _PLAYBGM_H_

#include "../../Framework/Pattern/BaseSingleton.h"
#include "SoundConfig.h"

//**************************************
// �N���X��`
//**************************************
class PlayBGM :
	public BaseSingleton<PlayBGM>
{
	friend class BaseSingleton<PlayBGM>;
public:
	// �t�F�[�h�C���A�t�F�[�h�A�E�g
	void FadeIn(SoundConfig::BGMID tag, float volume, int duration, bool isResume = true);
	void FadeOut(SoundConfig::BGMID tag, float volume, int duration, bool flagStop);
	void FadeOut();

	// �ꎞ��~�A�Đ��ĊJ
	void Pause(SoundConfig::BGMID tag);
	void Pause();
	void Resume(SoundConfig::BGMID tag);
	
	// ���O�ɍĐ����Ă���BGM���ꎞ��~���畜�A������
	void ResumePrev();

private:
	PlayBGM(){}
	~PlayBGM(){}

	SoundConfig::BGMID current;		//���݂�BGM
	SoundConfig::BGMID prev;		//1�O��BGM
};

#endif
