//=============================================================================
//
// ���O���͔w�i���� [NameEntryBgViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_BG_VIEWER_H_
#define _NAME_ENTRY_BG_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class ViewerAnimater;
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

	void SetBgIn(std::function<void()> Callback);
	void SetBgOut();
private:
	BaseViewerDrawer * congratsText;
	BaseViewerDrawer * newRecordText;
	BaseViewerDrawer * crown;
	ViewerAnimater *anim;

	bool sholudDraw;
	void AnimTexture(void);
	std::function<void()> Callback = nullptr;
	int currentTexPattern;
};
#endif