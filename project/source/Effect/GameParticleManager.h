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
		WhiteSmog,		//������
		ColorfulDebis,	//�J���t���f�u��
		ExplosionFlare,	//�΂̕�
		AngryFace,		//�{���
		TownExplosion,	//覐Δ���
		MeteorExplosion,//�~�T�C������
		Darkness,		//�ł̗��q(AI���x�������C�x���g)
		LinkLevelUp,	//�����N���x���A�b�v���G�t�F�N�g
		Cloud,			//�_
		EventInfo,		//�C�x���g�܂�
		BlueAura,		//�I�[��
		PunchEffect,	//�p���`�G�t�F�N�g
		GaudeDebris,	//�Q�[�W�j��
		EventHappen,	//�C�x���g�����G�t�F�N�g
		RouteTrace,		//���[�g�G�t�F�N�g
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

	//�`�揈��
	void Draw() override;

	//�����ł̃G�t�F�N�g�Z�b�g����
	void SetTownExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//覐Δ����̃G�t�F�N�g�Z�b�g����
	void SetMeteorExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//�{���̃G�t�F�N�g�Z�b�g����
	void SetAngryFaceEffect(std::function<void(void)> callback = nullptr);
	//�ł̗��q�̃G�t�F�N�g�Z�b�g����
	void SetDarknessEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback = nullptr);

	//�I�[���G�t�F�N�g�Z�b�g����
	BaseEmitter* SetAuraEffect(const D3DXVECTOR3& position, const D3DXVECTOR3& direction, std::function<void()> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif