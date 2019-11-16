//=============================================================================
//
// �A�ŃQ�[���^�C�}�[�r���A�[���� [BeatTimerViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_TIMER_VIEWER_H_
#define _BEAT_TIMER_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatTimerViewer :public BaseViewer
{
public:
	BeatTimerViewer();
	~BeatTimerViewer();

	void Update(void);
	void Draw(void);
	void Set(float time);

private:

	//�O�̃e�L�X�g(�h���Ɓh)
	BaseViewerDrawer * frontText;

	//���̃e�L�X�g(�h�b�h)
	BaseViewerDrawer * backText;

	//�����_
	BaseViewerDrawer *point;

	//������
	CountViewerDrawer *fewNum;

	//������
	CountViewerDrawer *intNum;

	//����
	float time;
};

#endif