//=====================================
//
// �K�C�h�r���A�[[GuideViewer.h]
// �@�\�F�K�C�h���L�����N�^�[�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GUIDEVIEWER_H_
#define _GUIDEVIEWER_H_

#include "GuideActor.h"
#include "GuideCamera.h"
#include "GuideViewerEffect.h"

//**************************************
// �N���X��`
//**************************************
class GuideViewer
{
private:
	GuideActor* actor;
	GuideCamera* camera;
	GuideViewerEffect* effect;

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

	static const D3DXVECTOR2 SubScreenSize;

};

#endif
