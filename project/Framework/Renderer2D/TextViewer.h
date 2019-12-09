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
class TextViewer : public GameObject
{
public:
	//�R���X�g���N�^
	//fontName : �g�p����t�H���g�̖��O ���t�H���g�t�@�C���ւ̃p�X�ł͂Ȃ��̂Œ���
	//size : �\���t�H���g�T�C�Y
	TextViewer(const char* fontName, int size);

	//�f�X�g���N�^
	~TextViewer();

	//�`�揈��
	void Draw();

	//���W�Z�b�g����
	void SetPos(int x, int y);

	//�J���[�Z�b�g����
	void SetColor(const D3DXCOLOR& color);

	//�\���e�L�X�g�Z�b�g����
	void SetText(const std::string& message);

	//�C�^���b�N�g�p�ݒ�
	void UseItalic(bool state);

private:
	//�t�H���g�C���^�[�t�F�C�X
	LPD3DXFONT font;
	LPD3DXFONT italicFont;

	//�t�H���g�T�C�Y
	int fontSize;

	//�\�����W
	int posX;
	int posY;

	//�s��
	int lineNum;

	//�\���J���[
	D3DXCOLOR color;

	//�C�^���b�N�g�p
	bool useItalic;

	//�\��������
#if _UNICODE
	wstring str;
#else
	std::string text;
#endif
};

#endif