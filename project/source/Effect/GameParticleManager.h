//=====================================
//
// GameParticleManager.h
// �@�\:�Q�[���V�[���̃p�[�e�B�N���}�l�[�W��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEPARTICLEMANAGER_H_
#define _GAMEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameParticleManager : public SceneParticleManager
{
public:
	enum ParticleID
	{
		BlueSpark,
		Max
	};

	void Init() override;
};

#endif