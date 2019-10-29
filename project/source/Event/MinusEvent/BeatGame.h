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

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatGame : public EventBase
{
private:
	int RemainFrame;
	int InputCount;
	bool TelopOver;
	std::function<void(bool)> Callback;

	// �e�L�X�g
	static TextViewer *Text;
	// �����_
	static BaseViewerDrawer *point;
	// ������
	static CountViewerDrawer *fewNum;
	// ������
	static CountViewerDrawer *intNum;

public:
	BeatGame(std::function<void(bool)> CallBack = nullptr);
	~BeatGame();
	void Update(void) override;
	void Draw(void) override;
	static void Init(void);
	static void Uninit(void);
	string GetEventMessage(int FieldLevel) override;
	void CountdownStart(void);
};

#endif
