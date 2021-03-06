//=============================================================================
//
// Gameシーンビュアー管理処理 [GameViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include <vector>
#include <functional>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewer;
class ItemStockViewer;
class TimerViewer;
class LevelViewer;
class GradeUpViewer;
class GradeFrameViewer;
class GradeNameViewer;
class TimeUpViewer;
class GameViewerParam;

//*****************************************************************************
// クラス定義
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

	//パラメータ受け取り
	void ReceiveParam(GameViewerParam&param);

	void SetActive(bool flag);
	void SetActive(bool flag, ViewerNo viewer);

	// グレードアップ演出
	void SetGradeUp(std::function<void(void)> Callback = nullptr);

	// グレードタイトル演出
	void SetGradeTitle(int fieldLevel, std::function<void(void)> Callback = nullptr);
	
	//タイムアップ演出
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

