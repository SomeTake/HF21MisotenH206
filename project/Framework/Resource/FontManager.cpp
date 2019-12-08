//=====================================
//
//FontManager.cpp
//�@�\:�t�H���g�}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FontManager.h"

/**************************************
�t�H���g���\�[�X�ǂݍ��ݏ���
***************************************/
void FontManager::LoadFont(const char* filePath)
{
	AddFontResource(filePath);
	loadFontContainer.push_back(filePath);
}

/**************************************
�t�H���g���\�[�X�������
***************************************/
void FontManager::RemoveFont(const char* filePath)
{
	RemoveFontResource(filePath);
}

/**************************************
�t�H���g�������
***************************************/
void FontManager::CleaaAll()
{
	for (auto&& pair : fontPool)
	{
		SAFE_RELEASE(pair.second);
	}
	fontPool.clear();

	for (auto&& pair : italicFontPool)
	{
		SAFE_RELEASE(pair.second);
	}
	italicFontPool.clear();

	for (auto&& path : loadFontContainer)
	{
		RemoveFont(path.c_str());
	}
}

/**************************************
�t�H���g�擾����
***************************************/
LPD3DXFONT FontManager::GetFont(const std::string & fontName)
{
	if (fontPool.count(fontName) == 0)
		_CreateFont(fontName);

	return fontPool[fontName];
}

/**************************************
�C�^���b�N�t�H���g�擾����
***************************************/
LPD3DXFONT FontManager::GetItalicFont(const std::string & fontName)
{
	if (italicFontPool.count(fontName) == 0)
		_CreateItalicFont(fontName);

	return italicFontPool[fontName];
}

/**************************************
�t�H���g�쐬�擾����
***************************************/
void FontManager::_CreateFont(const std::string & name)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPD3DXFONT font = NULL;
	D3DXCreateFont(pDevice, 10, 0, 0, D3DX_DEFAULT, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T(name.c_str()), &font);
}

/**************************************
�C�^���b�N�t�H���g�쐬����
***************************************/
void FontManager::_CreateItalicFont(const std::string & name)
{
}

/**************************************
�f�X�g���N�^
***************************************/
FontManager::~FontManager()
{
}
