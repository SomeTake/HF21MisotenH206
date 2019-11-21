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
#include "GuideActor.h"
#include "GuideCamera.h"
#include "GuideViewerBG.h"

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

	bool isActive;	// �`��۔���

	// �`��p�T�u�X�N���[�����쐬
	LPDIRECT3DTEXTURE9 renderTexture;
	LPDIRECT3DSURFACE9 renderSurface;
	LPDIRECT3DVERTEXBUFFER9 screenVtx;
	void MakeRenderTarget();
	void MakeScreen();

	static const D3DXVECTOR3 SubScreenPosition;

public:
	GuideViewer();
	~GuideViewer();

	void Update();
	void Draw();

	void ChangeAnim(GuideActor::AnimState next);
	void SetActive(bool flag);

	static const D3DXVECTOR2 SubScreenSize;

};

#endif
