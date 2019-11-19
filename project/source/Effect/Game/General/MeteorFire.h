//=============================================================================
//
// 覐Ύ���̉��G�t�F�N�g�N���X [MeteorFire.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _MeteorFire_H_
#define _MeteorFire_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	MeteorFireController�N���X
	***************************************/
	class MeteorFireController : public BaseParticleController
	{
	public:
		MeteorFireController();
	};

	/**************************************
	MeteorFire�N���X
	***************************************/
	class MeteorFire : public AnimationParticle3D
	{
	public:
		MeteorFire();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
		int AnimIndex;
	};
}
#endif