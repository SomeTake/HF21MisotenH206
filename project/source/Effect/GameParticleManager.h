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
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�Q�[���V�[���̃p�[�e�B�N���ʂ��ԍ�
***************************************/
namespace GameParticle
{
	enum ID
	{
		BlueSpark,		//�u���[�X�p�[�N
		BlueDebris,		//�u���[�X�p�[�N�̔j��
		WhiteSmog,		//������
		ColorfulDebis,	//�J���t���f�u��
		ExplosionFlare,	//�΂̕�
		MeteorExplosion,//覐Δ���
		MissileHit,		//�~�T�C������
		Max
	};
}

/**************************************
�N���X��`
***************************************/
class GameParticleManager : public SceneParticleManager, public BaseSingleton<GameParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	//����������
	void Init() override;

	//�V���M�������e�B�C�x���g�̃G�t�F�N�g�Z�b�g����
	void SetSingularityEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//覐Η����C�x���g�̃G�t�F�N�g�Z�b�g����
	void SetMeteorExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//�~�T�C�������C�x���g�̃G�t�F�N�g�Z�b�g����
	void SetMissileHitEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif