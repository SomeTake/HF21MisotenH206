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
class BaseViewer;
class ItemStockViewer;
class TimerViewer;
class LevelViewer;
class GradeUpViewer;
class GradeFrameViewer;
class GradeNameViewer;
class TimeUpViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class GameViewer
{
public:
	enum ViewerNo
	{
		ItemStock,
		Timer,
		Level,
		GradeUp,
		GradeFrame,
		GradeName,
		Max,
	};

	GameViewer();
	~GameViewer();

	void Update(void);
	void Draw(void);

	//�p�����[�^�󂯎��
	void ReceiveParam(GameViewerParam&param);

	void SetActive(bool flag);
	void SetActive(bool flag, ViewerNo viewer);

	// �O���[�h�A�b�v���o
	void SetGradeUp(std::function<void(void)> Callback = nullptr);

	// �O���[�h�^�C�g�����o
	void SetGradeTitle(int fieldLevel, std::function<void(void)> Callback = nullptr);
	
	//�^�C���A�b�v���o
	void SetTimeUp(std::function<void(void)> callback = nullptr);

	std::vector <BaseViewer*> gameViewer;

private:
	ItemStockViewer *stockViewer;
	TimerViewer *timerViewer;
	LevelViewer *levelViewer;
	GradeUpViewer *gradeUpViewer;
	GradeFrameViewer *gradeFrameViewer;
	GradeNameViewer *gradeNameViewer;
	TimeUpViewer *timeUpViewer;

	bool isActive;
};

#endif

