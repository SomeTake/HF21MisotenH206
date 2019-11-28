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
		MoveTail,		//�ړ��̋O��
		StarDust,		//�f�������̃X�^�[�_�X�g
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

	//�f���o��̃G�t�F�N�g�Z�b�g����
	void SetPlanetFallEffect(const D3DXVECTOR3 & position, BaseEmitter** MoveTail, BaseEmitter** StarDust);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};
#endif