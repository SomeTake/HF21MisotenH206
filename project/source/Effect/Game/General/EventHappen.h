//=====================================
//
// EventHappen.h
// �@�\:�C�x���g�����G�t�F�N�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EVENTHAPPEN_H_
#define _EVENTHAPPEN_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	EventHappenController
	***************************************/
	class EventHappenController : public BaseParticleController
	{
	public:
		EventHappenController();
	};

	/**************************************
	EventHappen
	***************************************/
	class EventHappen : public Particle3D
	{
	public:
		EventHappen();

		void Init();
		void Update();

	private:
		float initScale;
	};
}



#endif