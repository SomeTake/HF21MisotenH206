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
class ItemStockViewer;
class TimerViewer;
class LevelViewer;
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

	void SetActive(bool flag);

	std::vector <BaseViewer*> gameViewer;

private:
	ItemStockViewer *stockViewer;
	TimerViewer *timerViewer;
	LevelViewer *levelViewer;

	bool isActive;
};

#endif

