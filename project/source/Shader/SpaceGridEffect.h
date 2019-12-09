//=====================================
//
//SpaceGridEffect.h
//�@�\:�X�y�[�X�O���b�h�̕`��G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPACEGRIDEFFECT_H_
#define _SPACEGRIDEFFECT_H_

#include "../../main.h"
#include "../../Framework/Effect/SpriteEffect.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SpaceGridEffect : public SpriteEffect
{
public:
	SpaceGridEffect();
	~SpaceGridEffect();

	void SetAlpha(float alpha);

	void SetTime(float t);

private:
	LPDIRECT3DTEXTURE9 lumineMap;

	D3DXHANDLE hLumineTex;
	D3DXHANDLE hTime;
};
#endif