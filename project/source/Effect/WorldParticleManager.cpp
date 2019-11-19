//=====================================
//
//WorldParticleManager.cpp
//�@�\:���E���x���̃p�[�e�B�N���}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "WorldParticleManager.h"
#include "../../Framework/Particle/BaseParticleController.h"
#include "../../Framework/PostEffect/CrossFilterController.h"

#include "Game/World/Bubble.h"
#include "Game\World\WaterSmog.h"

/**************************************
static�����o
***************************************/
const float WorldParticleManager::BloomPower[3] = { 1.0f, 1.0f, 1.0f };
const float WorldParticleManager::BloomThrethold[3] = { 0.46f, 0.35f, 0.18f };

/**************************************
����������
***************************************/
void WorldParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(WorldParticle::Max, nullptr);
	controllers[WorldParticle::Bubble] = new Effect::Game::BubbleController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
�A�g�����e�B�X�G�t�F�N�g�Z�b�g����
***************************************/
void WorldParticleManager::SetAtlantisEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[WorldParticle::Bubble]->SetEmitter(position, callback);
}
