//=============================================================================
//
// ���̖��G�t�F�N�g�N���X [WaterSmog.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _WaterSmog_H_
#define _WaterSmog_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	WaterSmogController�N���X
	***************************************/
	class WaterSmogController : public BaseParticleController
	{
	public:
		WaterSmogController();
		void Update(void) override;
		static int FrameCount;
	};

	/**************************************
	WaterSmog�N���X
	***************************************/
	class WaterSmog : public AnimationParticle3D
	{
	public:
		WaterSmog();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;
	};
}
#endif