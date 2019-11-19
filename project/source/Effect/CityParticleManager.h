//=====================================
//
//CityParticleManager.h
//�@�\:�X���x���̃p�[�e�B�N���}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CITYPARTICLEMANAGER_H_
#define _CITYPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�X���x���̃p�[�e�B�N���ʂ��ԍ�
***************************************/
namespace CityParticle
{
	enum ID
	{
		BlueDebris,		//�u���[�X�p�[�N
		BlueSpark,		//�u���[�X�p�[�N�̔j��
		Max
	};
}

/**************************************
�N���X��`
***************************************/
class CityParticleManager : public SceneParticleManager, public BaseSingleton<CityParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	//����������
	void Init() override;

	//�V���M�������e�B�C�x���g�̃G�t�F�N�g�Z�b�g����
	void SetSingularityEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif