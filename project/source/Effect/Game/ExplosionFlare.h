//=============================================================================
//
// �΂̕��N���X [ExplosionFlare.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _ExplosionFlare_H_
#define _ExplosionFlare_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	ExplosionFlareController�N���X
	***************************************/
	class ExplosionFlareController : public BaseParticleController
	{
	public:
		ExplosionFlareController();
	};

	/**************************************
	ExplosionFlare�N���X
	***************************************/
	class ExplosionFlare : public AnimationParticle3D
	{
	public:
		ExplosionFlare();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;
		static const float MaxSpeed, MinSpeed;

		D3DXVECTOR3 directionMove;
		float speedMove;
	};
}
#endif