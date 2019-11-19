//=============================================================================
//
// �A�G�t�F�N�g�N���X [Bubble.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _Bubble_H_
#define _Bubble_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"

/**************************************
�O���錾
***************************************/

namespace Effect::Game
{
	/**************************************
	BubbleController�N���X
	***************************************/
	class BubbleController : public BaseParticleController
	{
	public:
		BubbleController();
	};

	/**************************************
	Bubble�N���X
	***************************************/
	class Bubble : public Particle3D
	{
	public:
		Bubble();

		void Init() override;
		void Update() override;

	private:
		static const int MinLife, MaxLife;
		static const float MinSpeed, MaxSpeed;

		const float Speed;
		const float Scale;
	};
}


#endif