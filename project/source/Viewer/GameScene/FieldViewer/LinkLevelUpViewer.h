
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

	//�e�L�X�g
	BaseViewerDrawer *text;

	//���j��
	BaseViewerDrawer *laurel;

	//����
	CountViewerDrawer *num;

	//�{
	BaseViewerDrawer *plus;

	//�A�j���[�V����
	ViewerAnimater *anim[AnimLayer::Max];

	//�R�[���o�b�N
	std::function<void()> Callback;

	//�w�i�o������
	void AppearBG(void);
	//�w�i��������
	void DisAppearBG(void);

	//�p�����[�^���󂯎�锠
	int parameterBox;
};

#endif