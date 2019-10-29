//=====================================
//
// BlueSpark.h
// �@�\:���X�p�[�N�G�t�F�N�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BLUESPARK_H_
#define _BLUESPARK_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

/**************************************
�O���錾
***************************************/

namespace Effect::Game
{
	/**************************************
	BlueSparkController�N���X
	***************************************/
	class BlueSparkController : public BaseParticleController
	{
	public:
		BlueSparkController();
	};

	/**************************************
	BlueSpark�N���X
	***************************************/
	class BlueSpark : public Particle3D
	{
	public:
		BlueSpark();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;

		float angleRotate;
		float initScaleX;
		float initScaleY;
	};
}


#endif