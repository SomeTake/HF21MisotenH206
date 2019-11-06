//=============================================================================
//
// �ړ��̎c���G�t�F�N�g�N���X [Tail.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _Tail_H_
#define _Tail_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

/**************************************
�O���錾
***************************************/

namespace Effect::Game
{
	/**************************************
	TailController�N���X
	***************************************/
	class TailController : public BaseParticleController
	{
	public:
		TailController();
	};

	/**************************************
	Tail�N���X
	***************************************/
	class Tail : public Particle3D
	{
	public:
		Tail();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
	};
}


#endif