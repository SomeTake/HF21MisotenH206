//=====================================
//
//RiverEffect.h
//�@�\:RiverActor�`��V�F�[�_
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RIVEREFFECT_H_
#define _RIVEREFFECT_H_

#include "../../main.h"
#include "../../Framework/Effect/RendererEffect.h"

namespace Field::Actor
{
	/**************************************
	�N���X��`
	***************************************/
	class RiverEffect : public RendererEffect
	{
	public:
		RiverEffect();
		~RiverEffect();

		void SetWorld(const Transform& transform);
		void SetUV(const D3DXVECTOR2& uv);

	private:
		D3DXHANDLE hTexUV;
	};
}

#endif