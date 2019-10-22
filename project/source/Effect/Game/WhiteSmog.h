//=====================================
//
//WhiteSmog.h
//�@�\:���X���b�O
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WHITESMOG_H_
#define _WHITESMOG_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/AnimationParticle.h"

namespace Effect::Game
{
	/**************************************
	WhiteSmogController�N���X
	***************************************/
	class WhiteSmogController : public BaseParticleController
	{
	public:
		WhiteSmogController();
	};

	/**************************************
	WhiteSmog�N���X
	***************************************/
	class WhiteSmog : public AnimationParticle
	{
	public:
		WhiteSmog();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;
		static const float MaxSpeed, MinSpeed;
	
		D3DXVECTOR3 directionMove;
		float speedMove;
	};
}
#endif