//=====================================
//
//AngryFace.h
//�@�\:�{���2D�p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ANGRYFACE_H_
#define _ANGRYFACE_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/2D/Particle2D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	AngryFaceController�N���X
	***************************************/
	class AngryFaceController : public BaseParticleController
	{
	public:
		AngryFaceController();
	};

	/**************************************
	AngryFace�N���X
	***************************************/
	class AngryFace : public Particle2D
	{
	public:
		AngryFace();
		~AngryFace();

		void Init();
		void Update();

	private:
		static const int Life;

		float targetScale;
	};
}
#endif