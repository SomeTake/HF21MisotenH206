//=============================================================================
//
// �ړ��̎c���G�t�F�N�g�N���X [MoveTail.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _MoveTail_H_
#define _MoveTail_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"

/**************************************
�O���錾
***************************************/

namespace Effect::Game
{
	/**************************************
	MoveTailController�N���X
	***************************************/
	class MoveTailController : public BaseParticleController
	{
	public:
		MoveTailController();
		void SetEmitterPos(D3DXVECTOR3 Pos);
		bool Draw() override;
	};

	/**************************************
	MoveTail�N���X
	***************************************/
	class MoveTail : public Particle3D
	{
	public:
		MoveTail();

		void Init() override;
		void Update() override;
	private:
		static const int Life;
	};
}


#endif