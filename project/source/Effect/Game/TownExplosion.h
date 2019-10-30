//=============================================================================
//
// �����ŃG�t�F�N�g�N���X [TownExplosion.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _TownExplosion_H_
#define _TownExplosion_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	TownExplosionController�N���X
	***************************************/
	class TownExplosionController : public BaseParticleController
	{
	public:
		TownExplosionController();
	};

	/**************************************
	TownExplosion�N���X
	***************************************/
	class TownExplosion : public AnimationParticle3D
	{
	public:
		TownExplosion();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
	};
}
#endif