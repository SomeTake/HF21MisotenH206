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

	virtual void SetLight(int index, const D3DLIGHT9& light);
	virtual void SetView(const D3DXMATRIX& viewMatrix);
	virtual void SetProjection(const D3DXMATRIX& projectionMatrix);

protected:
	static std::vector<D3DLIGHT9> lightContainer;
	static D3DXMATRIX mtxView;
	static D3DXMATRIX mtxProjection;
};

#endif