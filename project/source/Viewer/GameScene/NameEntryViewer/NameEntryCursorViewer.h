//=============================================================================
//
// ���O���̓J�[�\���r���A�[���� [NameEntryCursorViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_CURSOR_VIEWER_H_
#define _NAME_ENTRY_CURSOR_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NameEntryCursorViewer :public BaseViewer
{
public:
	NameEntryCursorViewer();
	~NameEntryCursorViewer();

	void Update();
	void Draw();

	//�J�[�\�����E�Ɉړ�
	void MoveCursorRight();

	//�J�[�\�������Ɉړ�
	void MoveCursorLeft();

private:

	//�J�[�\��
	BaseViewerDrawer * cursor;
};
#endif