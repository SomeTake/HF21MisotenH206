//=====================================
//
// BlueDebris.h
// 機能:青いスパークの破片エフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLUEDEBRIS_H_
#define _BLUEDEBRIS_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"

namespace Effect::Game
{
	/**************************************
	BlueDebrisControllerクラス
	***************************************/
	class BlueDebrisController : public BaseParticleController
	{
	public:
		BlueDebrisController();
	};

	/**************************************
	BlueDebrisクラス
	***************************************/
	class BlueDebris : public Particle3D
	{
	public:
		static const int MinLife, MaxLife;
		static const float MinSpeed, MaxSpeed;
		static const int TexDiv;

		BlueDebris();
		BlueDebris(const BlueDebris& rhs);

		void Init();
		void Update();

	private:

		const float InitSpeed;
		D3DXVECTOR3 moveDirection;
	};
}

#endif