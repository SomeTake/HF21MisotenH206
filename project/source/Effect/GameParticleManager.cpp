//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "Game/BlueSpark.h"
#include "Game/BlueDebris.h"
#include "Game/WhiteSmog.h"
#include "Game/ColorfulDebris.h"
#include "Game/ExplosionFlare.h"
#include "Game/TownExplosion.h"
#include "Game/MeteorExplosion.h"
#include "Game/AngryFace.h"
#include "Game/Darkness.h"
#include "Game/Bubble.h"
#include "Game/MoveTail.h"
#include "Game/SpaceTear.h"
#include "Game/LinkLevelUp.h"
#include "Game\StarRoad.h"

/**************************************
static�����o
***************************************/
const float GameParticleManager::BloomPower[3] = { 1.0f, 1.0f, 1.0f };
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
	controllers[GameParticle::AngryFace] = new Effect::Game::AngryFaceController();
	controllers[GameParticle::ExplosionFlare] = new Effect::Game::ExplosionFlareController();
	controllers[GameParticle::TownExplosion] = new Effect::Game::TownExplosionController();
	controllers[GameParticle::MeteorExplosion] = new Effect::Game::MeteorExplosionController();
	controllers[GameParticle::Darkness] = new Effect::Game::DarknessController();
	controllers[GameParticle::Bubble] = new Effect::Game::BubbleController();
	controllers[GameParticle::MoveTail] = new Effect::Game::MoveTailController();
	controllers[GameParticle::SpaceTear] = new Effect::Game::SpaceTearController();
	controllers[GameParticle::LinkLevelUp] = new Effect::Game::LinkLevelUpController();
	controllers[GameParticle::StarRoad] = new Effect::Game::StarRoadController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
�`�揈��
***************************************/
void GameParticleManager::Draw()
{
	SceneParticleManager::Draw();

	Debug::Begin("GameParticle");
	Debug::Text("starroad : %d", controllers[GameParticle::StarRoad]->GetParticleCount());
	Debug::End();
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

/**************************************
�����ł̃G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetTownExplosionEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	const D3DXVECTOR3 OffsetPosition = Vector3::Up * 10.0f;

	controllers[GameParticle::ExplosionFlare]->SetEmitter(position + OffsetPosition, callback);
	controllers[GameParticle::TownExplosion]->SetEmitter(position + OffsetPosition);
}

/**************************************
覐Δ����̃G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetMeteorExplosionEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[GameParticle::ExplosionFlare]->SetEmitter(position, callback);
	controllers[GameParticle::MeteorExplosion]->SetEmitter(position);
}

/**************************************
�{���̃G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetAngryFaceEffect(std::function<void(void)> callback)
{
	controllers[GameParticle::AngryFace]->SetEmitter(Vector3::Zero);
}

/**************************************
�ł̗��q�̃G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetDarknessEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[GameParticle::Darkness]->SetEmitter(position, nullptr);
}

/**************************************
�A�g�����e�B�X�̃G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetAtlantisEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[GameParticle::Bubble]->SetEmitter(position, nullptr);
}

/**************************************
�ړ��̋O�Ղ̃G�t�F�N�g�Z�b�g����
***************************************/
BaseEmitter* GameParticleManager::SetMoveTailEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	return controllers[GameParticle::MoveTail]->SetEmitter(position, nullptr);
}