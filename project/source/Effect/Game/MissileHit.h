//=============================================================================
//
// �~�T�C�������N���X [MissileHit.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _MissileHit_H_
#define _MissileHit_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	MissileHitController�N���X
	***************************************/
	class MissileHitController : public BaseParticleController
	{
	public:
		MissileHitController();
	};

	/**************************************
	MissileHit�N���X
	***************************************/
	class MissileHit : public AnimationParticle3D
	{
	public:
		MissileHit();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
		static const float Speed;

		float speedMove;
	};
}
#endif