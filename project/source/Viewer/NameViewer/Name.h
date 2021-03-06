//=====================================
//
// ネーム[Name.h]
// 機能：ネームのデータを保存するクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _NAME_H_
#define _NAME_H_

#include <string>

//**************************************
// クラス定義
//**************************************
class Name
{
private:
	int num[3];

public:
	Name();
	Name(int first, int second, int third);
	Name(const std::string& name);
	~Name();

	// コピーコンストラクタ
	Name(const Name& in);

	void Set(int first, int second, int third);

	int Get(int No);

	//コピー処理
	void Copy(const Name& rhs);
};

#endif
