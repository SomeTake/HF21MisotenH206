
//=============================================================================
//
// �����N���x���A�b�v�r���A�[���� [LinkLevelUpViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LINK_LEVEL_UP_VIEWER_H_
#define _LINK_LEVEL_UP_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;
class ViewerAnimater;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LinkLevelUpViewer :public BaseViewer
{
public:
	LinkLevelUpViewer();
	~LinkLevelUpViewer();

	void Update();
	void Draw(void);
	void Set(int level, std::function<void()> callback);

private:

	enum AnimLayer
	{
		Text,
		BG,
		Max
	};

	BaseViewerDrawer *text;
	BaseViewerDrawer *laurel;
	CountViewerDrawer *num;
	BaseViewerDrawer *plus;
	ViewerAnimater *anim[AnimLayer::Max];

	//�R�[���o�b�N
	std::function<void()> Callback;

	void AppearBG(void);
	void DisAppearBG(void);
	void SetNumPos(int level);

	//�p�����[�^���󂯎�锠
	int parameterBox;
};

#endif