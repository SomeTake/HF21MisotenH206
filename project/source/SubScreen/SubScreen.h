//=====================================
//
// �T�u�X�N���[��[SubScreen.cpp]
// �@�\�F�`��p�T�u�X�N���[���쐬�N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _SUBSCREEN_H_
#define _SUBSCREEN_H_

#include "../../main.h"

//**************************************
// �N���X��`
//**************************************
class SubScreen
{
private:
	// �`��p�T�u�X�N���[�����쐬
	LPDIRECT3DTEXTURE9 renderTexture;
	LPDIRECT3DSURFACE9 renderSurface;
	LPDIRECT3DSURFACE9 oldSuface;
	LPDIRECT3DVERTEXBUFFER9 screenVtx;
	void MakeRenderTarget();
	void MakeScreen();

	D3DXVECTOR2 size;
	D3DXVECTOR2 position;
public:
	SubScreen(D3DXVECTOR2 size, D3DXVECTOR2 position);
	~SubScreen();

	void DrawBegin();
	void DrawTexture();		// �s�N�Z���V�F�[�_�ɓn�����߂ɕ���
	void DrawEnd();
};

#endif