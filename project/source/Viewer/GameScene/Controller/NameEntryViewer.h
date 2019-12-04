//=============================================================================
//
// 名前登録ビュアーコントロール処理 [NameEntryViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_VIEWER_H_
#define _NAME_ENTRY_VIEWER_H_

#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class NameEntryInput;
class NameEntryReelViewer;
class NameEntryCursorViewer;
class BaseViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NameEntryViewer
{
public:
	NameEntryViewer();
	~NameEntryViewer();

	void Update(void);
	void Draw(void);

	//アクティブ状態をセット
	void SetActive(bool flag);

	//登録名ID取得処理（文字テーブルの0〜35までの値がentryNameMax個の配列）
	int* GetEntryNameID();

private:
	std::vector <BaseViewer*> nameEntryViewer;
	NameEntryInput *input;
	NameEntryReelViewer *reelViewer;
	NameEntryCursorViewer *cursorViewer;

	//カーソル移動処理
	void MoveCursor(void);

	//リール上下処理
	void UpDownReel(void);

	//登録名セット処理
	void SetEntryName();

	//登録できる名前の最大数
	static const int entryNameMax = 3;

	//登録名の文字テーブルID
	int entryNameID[entryNameMax];

	//リールカウント
	int reelCnt;

	//アクティブかどうか
	bool isActive;
};

#endif

