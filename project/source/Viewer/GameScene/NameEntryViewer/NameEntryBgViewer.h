//=============================================================================
//
// ���O���͔w�i���� [NameEntryBgViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_BG_VIEWER_H_
#define _NAME_ENTRY_BG_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NameEntryBgViewer :public BaseViewer
{
public:
	NameEntryBgViewer();
	~NameEntryBgViewer();

	void Update();
	void Draw(void);

private:

	//�o�^�ł��閼�O�̍ő吔
	static const int entryNameMax = 3;

	//�R���O���`�����[�V����
	BaseViewerDrawer * congratsText;
};

#endif