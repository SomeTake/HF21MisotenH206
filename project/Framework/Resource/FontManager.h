//=====================================
//
//FontManager.h
//�@�\:�t�H���g�}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"

#include <map>
#include <vector>

/**************************************
FontResourceKey�N���X
***************************************/
class FontResourceKey
{
	std::string fontName;
	int fontSize;

public:
	FontResourceKey(std::string name, int size);

	bool operator < (const FontResourceKey& rhs) const;

};

/**************************************
�N���X��`
***************************************/
class FontManager : public BaseSingleton<FontManager>
{
	friend class BaseSingleton<FontManager>;
public:

	void LoadFont(const char* filePath);
	void RemoveFont(const char* filePath);

	void ClearAll();

	LPD3DXFONT GetFont(const std::string& fontName, int fontSize);
	LPD3DXFONT GetItalicFont(const std::string& fontName, int fontSize);

private:
	void _CreateFont(const std::string& name, int fontSize);
	void _CreateItalicFont(const std::string& name, int fontSize);

	FontManager() {}
	FontManager(const FontManager&) {}

	~FontManager();
	
	std::map<FontResourceKey, LPD3DXFONT> fontPool;
	std::map<FontResourceKey, LPD3DXFONT> italicFontPool;
	std::vector<std::string> loadFontContainer;
};
#endif