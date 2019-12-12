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
	current = tag;
}

//=====================================
// �t�F�[�h�A�E�g
//=====================================
void PlayBGM::FadeOut(SoundConfig::BGMID tag, float volume, int duration, bool flagStop)
{
	BGM::Fade(tag, volume, duration, flagStop);
}

//=====================================
// �t�F�[�h�A�E�g
//=====================================
void PlayBGM::FadeOut()
{
	BGM::Fade(current, 0.1f, 30, true);
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
// �ꎞ��~
//=====================================
void PlayBGM::Pause()
{
	BGM::Stop(current);
	prev = current;
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
	current = prev;
}
