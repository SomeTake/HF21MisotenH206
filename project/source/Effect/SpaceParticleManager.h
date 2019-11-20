//=====================================
//
//SpaceParticleManager.h
//�@�\:�F�����x���̃p�[�e�B�N���}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPACEPARTICLEMANAGER_H_
#define _SPACEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�O���錾
***************************************/
namespace SpaceParticle
{
	enum ID
	{
		SpaceTear,		//����f��̃X�p�[�N,
		StarRoad,		//��͓�
		Blackhole,		//�u���b�N�z�[��
		Max
	};
}

/**************************************
�N���X��`
***************************************/
class SpaceParticleManager : public SceneParticleManager, public BaseSingleton<SpaceParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	void Init() override;

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};
#endif