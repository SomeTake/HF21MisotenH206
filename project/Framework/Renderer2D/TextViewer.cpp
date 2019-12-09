//=====================================
//
//TextViewer.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TextViewer.h"
#include "../Resource/FontManager.h"

/**************************************
�R���X�g���N�^
***************************************/
TextViewer::TextViewer(const char * fontName, int fontSize) :
	font(NULL),
	fontSize(fontSize),
	posX(10),
	posY(10),
	lineNum(1),
	color(0xffffffff),
	text(""),
	useItalic(false)
{
	font = FontManager::Instance()->GetFont(fontName, fontSize);
	italicFont = FontManager::Instance()->GetItalicFont(fontName, fontSize);
}

/**************************************
�f�X�g���N�^
***************************************/
TextViewer::~TextViewer()
{
	SAFE_RELEASE(font);
	SAFE_RELEASE(italicFont);
}

/**************************************
�`�揈��
***************************************/
void TextViewer::Draw(bool FromLeft)
{
	if (!FromLeft)
	{
		//�e�L�X�g�𒆉��񂹂ŕ\�����邽�߂�Rect���v�Z
		LONG left = posX - text.length() * fontSize / 2;
		LONG top = posY - fontSize / 2 * lineNum;
		LONG right = left + text.length() * fontSize;
		LONG bottom = top + fontSize * lineNum;

		//�`��
		RECT rect = { left, top, right, bottom };

		if (!useItalic)
			font->DrawText(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_NOCLIP, color);
		else
			italicFont->DrawText(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_NOCLIP, color);
	}
	else
	{
		//�e�L�X�g�����l�߂ŕ\�����邽�߂�Rect���v�Z
		LONG left = posX;
		LONG top = posY - fontSize / 2 * lineNum;
		LONG right = left + text.length() * fontSize;
		LONG bottom = top + fontSize * lineNum;

		//�`��
		RECT rect = { left, top, right, bottom };
		font->DrawText(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_VCENTER, color);
	}
}

/**************************************
���W�Z�b�g����
***************************************/
void TextViewer::SetPos(int x, int y)
{
	posX = x;
	posY = y;
}

/**************************************
���W�Z�b�g����
***************************************/
void TextViewer::SetColor(const D3DXCOLOR & color)
{
	this->color = color;
}

/**************************************
�e�L�X�g�Z�b�g����
***************************************/
void TextViewer::SetText(const std::string & message)
{
	//���s���������čs�����Z�b�g
	lineNum = 1 + (std::count(message.cbegin(), message.cend(), '\n'));

	text = message;
}

/**************************************
�C�^���b�N�g�p�ݒ�
***************************************/
void TextViewer::UseItalic(bool state)
{
	useItalic = state;
}
