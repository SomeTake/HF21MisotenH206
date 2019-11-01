//=============================================================================
//
// 覐Δ����G�t�F�N�g�N���X [MeteorExplosion.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _MeteorExplosion_H_
#define _MeteorExplosion_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	MeteorExplosionController�N���X
	***************************************/
	class MeteorExplosionController : public BaseParticleController
	{
	public:
		MeteorExplosionController();
	};

	/**************************************
	MeteorExplosion�N���X
	***************************************/
	class MeteorExplosion : public AnimationParticle3D
	{
	public:
		MeteorExplosion();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
	};
}
#endif