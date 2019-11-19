//=====================================
//
//LinkLevelUp.h
//�@�\:�����N���x���A�b�v����2D�p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _LINKLEVELUP_H_
#define _LINKLEVELUP_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/2D/Particle2D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	LinkLevelUpController
	***************************************/
	class LinkLevelUpController : public BaseParticleController
	{
	public:
		LinkLevelUpController();
	};

	/**************************************
	LinkLevelUp�N���X
	***************************************/
	class LinkLevelUp : public Particle2D
	{
	public:
		LinkLevelUp();
		~LinkLevelUp();

		void Init();
		void Update();

	private:
		D3DXVECTOR3 directionMove;
		float speed;
		float initScale;
	};
}
#endif