//=============================================================================
//
// 名前登録ビュアーコントロール処理 [NameEntryViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_VIEWER_H_
#define _NAME_ENTRY_VIEWER_H_

#include <vector>
#include <string>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class NameEntryInput;
class NameEntryReelViewer;
class NameEntryBgViewer;
class NameEntryInfoViewer;
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

	void Init(void);
	void Update(void);
	void Draw(void);

	//アクティブ状態をセット
	void SetActive(bool flag);
	bool GetIsActive(void);

	//登録名ID取得処理（文字テーブルの0〜35までの値がentryNameMax個の配列）
	std::string GetEntryNameID();

	void SlideNameEntryViewer(bool isIn);

	// プレイヤーネームが入力されたフラグを制御する（ライ）
	bool GetNameEntered(void) { return this->NameEntered; };
	void SetNameEntered(bool Flag) { this->NameEntered = Flag; };
	
	// スライドインが終わったかどうかのフラグを取得
	bool GetSlideOver(void);

private:
	std::vector <BaseViewer*> nameEntryViewer;
	NameEntryInput *input;
	NameEntryReelViewer *reelViewer;
	NameEntryBgViewer *bgViewer;

	//カーソル移動処理
	void MoveCursor(void);

	//リール上下処理
	void UpDownReel(void);

	//登録名セット処理
	void SetEntryName();

	// int型のネームがstring型に変換
	std::string IntToString(int NameInt);

	//登録できる名前の最大数
	static const int entryNameMax = 3;

	//登録名の文字テーブルID
	int entryNameID[entryNameMax];

	//リールカウント
	int reelCnt;

	//アクティブかどうか
	bool isActive;

	// プレイヤーネームが入力されたかどうか
	bool NameEntered;
};

#endif

