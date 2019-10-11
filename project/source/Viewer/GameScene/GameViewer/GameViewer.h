//=============================================================================
//
// Game�V�[���r���A�[�Ǘ����� [GameViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class StockViewer;
class TimerViewer;
class LevelViewer;
class GameViewerParam;

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
	
private:
	int baseViewerMax;

	StockViewer *stockViewer;
	TimerViewer *timerViewer;
	LevelViewer *levelViewer;
	GameViewerParam *gameViewerParam;
};

#endif

