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
		AngryFace,		//�{���
		TownExplosion,	//覐Δ���
		MeteorExplosion,//�~�T�C������
		Darkness,		//�ł̗��q(AI���x�������C�x���g)
		Bubble,			//���̖A
		MoveTail,		//�ړ��̋O��
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
	//�����ł̃G�t�F�N�g�Z�b�g����
	void SetTownExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//覐Δ����̃G�t�F�N�g�Z�b�g����
	void SetMeteorExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//�{���̃G�t�F�N�g�Z�b�g����
	void SetAngryFaceEffect(std::function<void(void)> callback = nullptr);
	//�ł̗��q�̃G�t�F�N�g�Z�b�g����
	void SetDarknessEffect(const D3DXVECTOR3 & position,std::function<void(void)> callback = nullptr);
	//�A�g�����e�B�X�̃G�t�F�N�g�Z�b�g����
	void SetArtlantisEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback = nullptr);
	//�ړ��̋O�Ղ̃G�t�F�N�g�Z�b�g����
	BaseEmitter* SetMoveTailEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif