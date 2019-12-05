//=====================================
//
//PunchEffect.h
//�@�\:�p���`�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PUNCHEFFECT_H_
#define _PUNCHEFFECT_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	PunchEffectController
	***************************************/
	class PunchEffectController : public BaseParticleController
	{
	public:
		PunchEffectController();
	};

	/**************************************
	PunchEffect
	***************************************/
	class PunchEffect : public Particle3D
	{
	public:
		PunchEffect();

		void Init();
		void Update();

	private:
		float initScale;
		D3DXVECTOR3 moveDir;
	};
}


#endif