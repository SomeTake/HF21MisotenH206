//=====================================
//
//�T�E���h�ݒ菈��[SoundConfig.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "SoundConfig.h"

/**************************************
static�����o
***************************************/
const char* SoundConfig::BGMPath[BGMID::BGMMax]
{
	{"data/SOUND/BGM/MusMus-BGM-052.wav"},
	{"data/SOUND/BGM/MusMus-BGM-067.wav"},
	{"data/SOUND/BGM/Es-STAGE1_loop.wav"},
	{"data/SOUND/BGM/Labyrinth-Of-Time_loop.wav"},
	{"data/SOUND/BGM/Battle-Forbidden_loop.wav"},
	{"data/SOUND/BGM/Battle-Noble_loop.wav"},
	{"data/SOUND/BGM/Crasher_loop.wav"},
	{"data/SOUND/BGM/MusMus-CT-NV-TT.wav"}
};

const char* SoundConfig::SEPath[SEID::SEMax]
{
	// *** Voice ***
	{"data/SOUND/VOICE/robo/AIBonus.wav"},
	{"data/SOUND/VOICE/robo/AIOutofControll.wav"},
	{"data/SOUND/VOICE/robo/AIOutofControllStop.wav"},
	{"data/SOUND/VOICE/robo/AllLinkLevelUp.wav"},
	{"data/SOUND/VOICE/robo/DevelopSpeedUp.wav"},
	{"data/SOUND/VOICE/robo/DrillStock.wav"},
	{"data/SOUND/VOICE/robo/LinkLevelDown.wav"},
	{"data/SOUND/VOICE/robo/LinkLevelUp.wav"},
	{"data/SOUND/VOICE/robo/MeteorBreakFailed.wav"},
	{"data/SOUND/VOICE/robo/MeteorBreakSuccess.wav"},
	{"data/SOUND/VOICE/robo/NewContinent.wav"},
	{"data/SOUND/VOICE/robo/NewStar.wav"},
	{"data/SOUND/VOICE/robo/NewTown.wav"},
	{"data/SOUND/VOICE/robo/TimeLimitHeal.wav"},
	{"data/SOUND/VOICE/robo/UMAFailed.wav"},
	{"data/SOUND/VOICE/robo/UMAStop.wav"},
	{"data/SOUND/VOICE/Ready.wav"},
	{"data/SOUND/VOICE/GameStart.wav"},
	{"data/SOUND/VOICE/FieldLevelUp.wav"},
	{"data/SOUND/VOICE/NextField.wav"},
	{"data/SOUND/VOICE/NewRecord.wav"},
	{"data/SOUND/VOICE/NewReward.wav"},
	{"data/SOUND/VOICE/ButtonMashing.wav"},
	{"data/SOUND/VOICE/Destructer.wav"},
	{"data/SOUND/VOICE/Artist.wav"},
	{"data/SOUND/VOICE/Linker.wav"},
	{"data/SOUND/VOICE/MinusMaster.wav"},
	{"data/SOUND/VOICE/PlusMaster.wav"},
	{"data/SOUND/VOICE/Pioneer.wav"},
	{"data/SOUND/VOICE/MasterAI.wav"},
	{"data/SOUND/VOICE/MinusComplete.wav"},
	{"data/SOUND/VOICE/PlusComplete.wav"},

	// *** ME ***
	{"data/SOUND/ME/MusMus-JGL-004.wav"},
	{"data/SOUND/ME/MusMus-JGL-023.wav"},
	{"data/SOUND/ME/MusMus-JGL-026.wav"},

	// *** SE ***
	{"data/SOUND/SE/kettei-02.wav"},
	{"data/SOUND/SE/btn02.wav"},
	{"data/SOUND/SE/btn03.wav"},
	{"data/SOUND/SE/btn01.wav"},
	{"data/SOUND/SE/Onmtp-Impact01-1.wav"},
	{"data/SOUND/SE/punch_09.wav"},			// �f���N�V
	{"data/SOUND/SE/gong-played1.wav"},
	{"data/SOUND/SE/gong-played2.wav"},
	{"data/SOUND/SE/quiz-right_02.wav"},	// �s���|���s���|�[��
	{"data/SOUND/SE/quiz-wrong_02.wav"},	// �u�u�[
	{"data/SOUND/SE/land-the-spaceship_02.wav"},	// �������[�[�[�[�[�����[�[�[�[�[��i�ʂ�߂��鉹�j
	{"data/SOUND/SE/magic-electron3.wav"},
	{"data/SOUND/SE/magic-quake2.wav"},
	{"data/SOUND/SE/wind_04.wav"},			// ���S�I�I�I�I�I�I�I�I�I�I�I�I
	{"data/SOUND/SE/alrat_02.wav"},			// �x��
	{"data/SOUND/SE/othr11.wav"},
	{"data/SOUND/SE/se_amd05.wav"},
	{"data/SOUND/SE/chime_01.wav"},			// �s���|�[��
	{"data/SOUND/SE/blast_05.wav"},			// ����
	{"data/SOUND/SE/fly-a-spaceship_04.wav"},	// ���ɂ�ɂ�ɂ�
	{"data/SOUND/SE/eye-shine1.wav"},
	{"data/SOUND/SE/police-whistle2.wav"},
	{"data/SOUND/SE/kira1.wav"},
	{"data/SOUND/SE/recollection1.wav"},
	{"data/SOUND/SE/clapping-hands1.wav"},
	{"data/SOUND/SE/data-analysis1.wav"},
	{"data/SOUND/SE/alien1.wav"},
	{"data/SOUND/SE/cancel2.wav"}
};

const float SoundConfig::VolumeVoice = 1.0f;
const float SoundConfig::VolumeBGM = 0.3f;

/**************************************
���݂̃��x���ł�BGM��ID�擾����
***************************************/
SoundConfig::BGMID SoundConfig::GetBgmID(int fieldLevel)
{
	if (fieldLevel == 0)
		return City;

	if (fieldLevel == 1)
		return World;

	if (fieldLevel == 2)
		return Space;

	return City;
}
