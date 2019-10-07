//=============================================================================
//
// Game�V�[���r���A�[�Ǘ����� [GameViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class StockViewer;
class TimerViewer;
class LevelViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class GameViewer:public BaseViewer
{
public:
	GameViewer();
	~GameViewer();

	void Update(void);
	void Draw(void);

	void ReceiveParam();

private:
	int baseViewerMax;

	StockViewer *stockViewer;
	TimerViewer *timerViewer;
	LevelViewer *levelViewer;
};

#endif

