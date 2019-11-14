//=============================================================================
//
// �A�ŃQ�[���C�x���g�N���X [BeatGame.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _BeatGame_H_
#define _BeatGame_H_

#include "../EventBase.h"
#include <functional>
#include <string>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;
class TextViewer;
class BeatGameViewerOrigin;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatGame : public EventBase
{
private:
	int RemainFrame;
	int InputCount;
	bool TelopOver;
	bool IsDrawingViewer;
	bool IsSuccess;
	BeatGameViewerOrigin *Viewer;
	std::function<void(bool)> Callback;

	void EventOver(void);

	// �e�L�X�g
	TextViewer *Text;
	TextViewer *CountdownText;
	// �����_
	BaseViewerDrawer *point;
	// ������
	CountViewerDrawer *fewNum;
	// ������
	CountViewerDrawer *intNum;

public:
	BeatGame(std::function<void(bool)> CallBack = nullptr);
	~BeatGame();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void CountdownStart(void);
};

#endif
