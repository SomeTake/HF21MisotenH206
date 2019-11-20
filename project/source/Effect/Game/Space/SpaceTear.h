//=====================================
//
//SpaceTear.h
//�@�\:����f��p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPACETEAR_H_
#define _SPACETEAR_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseEmitter.h"

namespace Effect::Game
{
	/**************************************
	SpaceTearController�N���X
	***************************************/
	class SpaceTearController : public BaseParticleController
	{
	public:
		SpaceTearController();
	};

	/**************************************
	SpaceTear�N���X
	***************************************/
	class SpaceTear : public Particle3D
	{
	public:
		SpaceTear();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;

		float angleRotate;
		float initScaleX;
		float initScaleY;
	};

	/**************************************
	SpaceTearEmitter�N���X
	***************************************/
	class SpaceTearEmitter : public BaseEmitter
	{
	public:
		SpaceTearEmitter();

		bool IsActive() const override;
	};
}
#endif