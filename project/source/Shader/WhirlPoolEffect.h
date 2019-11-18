//=====================================
//
//WhirlPool.h
//�@�\:�Q�������_���[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WHIRLPOOL_H_
#define _WHIRLPOOL_H_

#include "../../main.h"
#include "../../Framework/Effect/RendererEffect.h"

namespace Field::Actor
{
	/**************************************
	�N���X��`
	***************************************/
	class WhirlPoolEffect : public RendererEffect
	{
	public:
		WhirlPoolEffect();
		~WhirlPoolEffect();

		void SetWorld(const Transform& transform);

		void SetTime(float t);

	private:
		D3DXHANDLE hTime;

	};
}


#endif