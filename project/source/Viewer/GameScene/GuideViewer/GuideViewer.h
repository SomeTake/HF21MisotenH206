//=====================================
//
// �K�C�h�r���A�[[GuideViewer.h]
// �@�\�F�K�C�h���L�����N�^�[�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GUIDEVIEWER_H_
#define _GUIDEVIEWER_H_

#include "../../../../Framework/PostEffect/Effect/CRTFilter.h"
#include <string>
#include "GuideActor.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class GuideCamera;
class GuideViewerBG;
class GuideCallOutViewer;
class SubScreen;

//**************************************
// �N���X��`
//**************************************
class GuideViewer
{
private:
	// �e��C���X�^���X�p�|�C���^
	GuideActor* actor;
	GuideCamera* camera;
	GuideViewerBG* bg;
	CRTFilter* filter;
	GuideCallOutViewer *callOutViewer;
	SubScreen* subScreen;

	bool isActive;	// �`��۔���

	static const D3DXVECTOR2 SubScreenPosition;
	static const D3DXVECTOR2 SubScreenSize;

public:
	GuideViewer();
	~GuideViewer();

	void Update();
	void Draw();

	void ChangeAnim(GuideActor::AnimState next);
	void SetActive(bool flag);

	//�K�C�h�r���A�[�Z�b�g
	void SetGuideViewer(const std::string &message);
};

#endif
