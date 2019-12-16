//=====================================
//
//RouteEffect.h
//�@�\:���[�g�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ROUTEEFFECT_H_
#define _ROUTEEFFECT_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	RouteEffectController
	***************************************/
	class RouteEffectController : public BaseParticleController
	{
	public:
		RouteEffectController();
	};

	/**************************************
	RouteEffect
	***************************************/
	class RouteEffect : public Particle3D
	{
	public:
		RouteEffect();

		void Init();
		void Update();

		static const float InitSpeed;

	private:
		D3DXVECTOR3 moveDir;
	};
}

#endif