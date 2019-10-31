//=============================================================================
//
// �����G�t�F�N�g�N���X [Explosion.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _Explosion_H_
#define _Explosion_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	ExplosionController�N���X
	***************************************/
	class ExplosionController : public BaseParticleController
	{
	public:
		ExplosionController();
	};

	/**************************************
	Explosion�N���X
	***************************************/
	class Explosion : public AnimationParticle3D
	{
	public:
		Explosion();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
	};
}
#endif