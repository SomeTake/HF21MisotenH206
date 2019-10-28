//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"

#include "Game/BlueSpark.h"
#include "Game/BlueDebris.h"
#include "Game/WhiteSmog.h"
#include "Game/ColorfulDebris.h"

/**************************************
static�����o
***************************************/
const float GameParticleManager::BloomPower[3] = {1.0f, 1.0f, 1.0f};
const float GameParticleManager::BloomThrethold[3] = { 0.46f, 0.35f, 0.18f };

/**************************************
����������
***************************************/
void GameParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(GameParticle::Max, NULL);
	controllers[GameParticle::BlueSpark] = new Effect::Game::BlueSparkController();
	controllers[GameParticle::BlueDebris] = new Effect::Game::BlueDebrisController();
	controllers[GameParticle::WhiteSmog] = new Effect::Game::WhiteSmogController();
	controllers[GameParticle::ColorfulDebis] = new Effect::Game::ColorfulDebrisController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
�V���M�������e�B�G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetSingularityEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	const D3DXVECTOR3 OffsetPosition = Vector3::Up * 10.0f;

	//BlueDebris�̕��̕��o���Ԃ��������߂ɂ��Ă���̂ŁABlueDebris�ɃR�[���o�b�N��ݒ肷��
	controllers[GameParticle::BlueSpark]->SetEmitter(position + OffsetPosition);
	controllers[GameParticle::BlueDebris]->SetEmitter(position + OffsetPosition, callback);
}
