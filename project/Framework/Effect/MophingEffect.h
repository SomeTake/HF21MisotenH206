//=====================================
//
//MophingEffect.h
//�@�\:���[�t�B���O�p�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MOPHINGEFFECT_H_
#define _MOPHINGEFFECT_H_

#include "../../main.h"
#include "RendererEffect.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class MophingEffect : public RendererEffect
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	MophingEffect();
	~MophingEffect();

	void SetTime(float t);

private:
	//�V�F�[�_�ւ̃n���h��
	D3DXHANDLE hTechnique;
	D3DXHANDLE hTime;
};
#endif