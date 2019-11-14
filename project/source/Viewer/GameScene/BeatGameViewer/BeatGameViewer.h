//=============================================================================
//
// �A�ŃQ�[���r���A�[�Ǘ����� [BeatGameViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_GAME_VIEWER_H_
#define _BEAT_GAME_VIEWER_H_

#include <vector>
#include "BeatTitleViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewer;
class BeatTitleViewer;
class BeatGaugeViewer;
class BeatTimerViewer;
class BeatStarterViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatGameViewer
{
public:
	BeatGameViewer();
	~BeatGameViewer();

	void Update(void);
	void Draw(void);

	//�A�ŃQ�[���̃^�C�g����ݒu����
	void SetGameTitle(BeatTitleViewer::TitleID id);

	//�A�ŃQ�[���̃Q�[�W��ݒu����
	void SetGameGauge(float percent);

	//�A�ŃQ�[���̎c�莞�Ԃ�ݒ肷��
	void SetRemainTime(float time);

	//�uReady�v��\������
	void SetReady(void);

	//�uGO�v��\������
	void SetGo(void);

private:
	std::vector <BaseViewer*> beatGameViewer;
	BeatTitleViewer *titleViewer;
	BeatGaugeViewer *gaugeViewer;
	BeatTimerViewer *timerViewer;
	BeatStarterViewer *starterViewer;
};

#endif

