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
	BaseViewerDrawer * congratsText;
	BaseViewerDrawer * newRecordText;
	BaseViewerDrawer * crown;

	void AnimTexture(void);

	int currentTexPattern;
};
#endif