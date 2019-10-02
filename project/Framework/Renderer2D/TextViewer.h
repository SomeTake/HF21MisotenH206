//=====================================
//
//TextViewer.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TEXTVIEWER_H_
#define _TEXTVIEWER_H_

#include "../../main.h"

#include <string>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TextViewer
{
public:
	TextViewer(const char* fontName, int size);
	~TextViewer();

	void Draw();

	void SetPos(int x, int y);

	void SetColor(const D3DXCOLOR& color);

	void SetText(const std::string& message);

	static void LoadFont(const char* fontFileName);

private:
	//�t�H���g�C���^�[�t�F�C�X
	ID3DXFont * font;

	//�t�H���g�T�C�Y
	int fontSize;

	//�\�����W
	int posX;
	int posY;

	//�\���J���[
	D3DXCOLOR color;

	//�\��������
#if _UNICODE
	wstring str;
#else
	std::string text;
#endif
};

#endif