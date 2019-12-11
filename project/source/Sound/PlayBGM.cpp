//=====================================
//
// �v���CBGM[PlayBGM.h]
// �@�\�F���U���g���
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PlayBGM.h"
#include "../../Framework/Sound/BackgroundMusic.h"

//=====================================
// �t�F�[�h�C��
//=====================================
void PlayBGM::FadeIn(SoundConfig::BGMID tag, float volume, int duration)
{
	BGM::FadeIn(tag, volume, duration);
}

//=====================================
// �t�F�[�h�A�E�g
//=====================================
void PlayBGM::FadeOut(SoundConfig::BGMID tag, float volume, bool flagStop)
{
	BGM::Fade(tag, volume, flagStop);
}

//=====================================
// �ꎞ��~
//=====================================
void PlayBGM::Pause(SoundConfig::BGMID tag)
{
	BGM::Stop(tag);
	prev = tag;
}

//=====================================
// �Đ��ĊJ
//=====================================
void PlayBGM::Resume(SoundConfig::BGMID tag)
{
	BGM::Resume(tag);
}

//=====================================
// ���O�ɍĐ����Ă���BGM���ꎞ��~���畜�A
//=====================================
void PlayBGM::ResumePrev()
{
	BGM::Resume(prev);
}
