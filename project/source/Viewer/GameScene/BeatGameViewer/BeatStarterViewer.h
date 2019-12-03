//=============================================================================
//
// �A�ŃQ�[���X�^�[�^�[�r���A�[���� [BeatStarterViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_STARTER_VIEWER_H_
#define _BEAT_STARTER_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class ViewerAnimater;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatStarterViewer :public BaseViewer
{
public:
	BeatStarterViewer();
	~BeatStarterViewer();

	void Update();
	void Draw(void);
	void SetReady(void);
	void SetGo(void);

private:
	enum TextType
	{
		Ready,
		Go,
		Max
	};

	BaseViewerDrawer *readyText;
	BaseViewerDrawer *goText;
	ViewerAnimater *anim[TextType::Max];

	//���f�B�[���ׂ���
	bool shouldReady;
	//�S�[���ׂ���
	bool shouldGo;
};

#endif