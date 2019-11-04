//=====================================
//
// RendererEffect.h
// �@�\:�`��G�t�F�N�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RENDEREREFFECT_H_
#define _RENDEREREFFECT_H_

#include "../../main.h"

#include <vector>

/**************************************
�N���X��`
***************************************/
class RendererEffect
{
public:
	RendererEffect() {}
	virtual ~RendererEffect() {}

	//���C�g���ݒ菈��
	static void SetLight(int index, const D3DLIGHT9& light);

	//�r���[�A�v���W�F�N�V�����s��ݒ菈��
	static void SetView(const D3DXMATRIX& viewMatrix);
	static void SetProjection(const D3DXMATRIX& projectionMatrix);
	
	//�ύX���f����
	void Commit(); 
	virtual void CommitLightAndCamera() = 0;

	//�`��J�n�錾�A�`��I���錾
	void Begin();
	void BeginPass(DWORD pass);
	void EndPass();
	void End();

protected:
	LPD3DXEFFECT effect;

	static std::vector<D3DLIGHT9> lightContainer;
	static D3DXMATRIX mtxView;
	static D3DXMATRIX mtxProjection;
};

#endif