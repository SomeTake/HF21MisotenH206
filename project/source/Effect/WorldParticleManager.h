//=====================================
//
//WorldParticleManager.h
//�@�\:���E���x���̃p�[�e�B�N���}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WRORLDPARTICLEMANAGER_H_
#define _WRORLDPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
���[���h���x���̃p�[�e�B�N���ʂ��ԍ�
***************************************/
namespace WorldParticle
{
	enum ID
	{
		Bubble,				//���̖A
		WhirlPoolBubble,	//�Q���̖A
		Max
	};
}

/**************************************
�N���X��`
***************************************/
class WorldParticleManager : public SceneParticleManager, public BaseSingleton<WorldParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	void Init() override;

	//�A�g�����e�B�X�̃G�t�F�N�g�Z�b�g����
	void SetAtlantisEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif