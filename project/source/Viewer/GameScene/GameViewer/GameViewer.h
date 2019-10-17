//=============================================================================
//
// Game�V�[���r���A�[�Ǘ����� [GameViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include <vector>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class StockViewer;
class TimerViewer;
class LevelViewer;
class GameViewerParam;
class BaseViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class GameViewer
{
public:
	GameViewer();
	~GameViewer();

	void Update(void);
	void Draw(void);

	//�p�����[�^�󂯎��
	void ReceiveParam(GameViewerParam&param);

	std::vector <BaseViewer*> baseViewer;

private:
	int baseViewerMax;

	StockViewer *stockViewer;
	TimerViewer *timerViewer;
	LevelViewer *levelViewer;
	GameViewerParam *gameViewerParam;
};

#endif
