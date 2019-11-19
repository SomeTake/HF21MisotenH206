//=============================================================================
//
// AI���x�������G�t�F�N�g�N���X [Darkness.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _Darkness_H_
#define _Darkness_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	DarknessController�N���X
	***************************************/
	class DarknessController : public BaseParticleController
	{
	public:
		DarknessController();
	};

	/**************************************
	Darkness�N���X
	***************************************/
	class Darkness : public Particle3D
	{
	public:

		Darkness();

		void Init() override;
		void Update() override;

	private:
		static const int MinLife, MaxLife;
		static const float MinSpeed, MaxSpeed;
		static const int TexDiv;
		const float Speed;
	};
}
#endif