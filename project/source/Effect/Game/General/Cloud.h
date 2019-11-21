//=====================================
//
//Cloud.h
//�@�\:�_�p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CLOUDY_H_
#define _CLOUDY_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/2D/Particle2D.h"

namespace Effect::Game
{
	/**************************************
	CloudController�N���X
	***************************************/
	class CloudController : public BaseParticleController
	{
	public:
		CloudController();
	};

	/**************************************
	Cloud�N���X
	***************************************/
	class Cloud : public Particle2D
	{
	public:
		Cloud();

		void Init() override;
		void Update() override;

	private:
		D3DXVECTOR3 velocity;
	};
}

#endif