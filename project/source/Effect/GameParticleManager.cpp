//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Particle/BaseParticleController.h"

#include "Game/General/WhiteSmog.h"
#include "Game/General/ColorfulDebris.h"
#include "Game/General/ExplosionFlare.h"
#include "Game/General/TownExplosion.h"
#include "Game/General/MeteorExplosion.h"
#include "Game/General/AngryFace.h"
#include "Game/General/Darkness.h"
#include "Game/General/LinkLevelUp.h"
#include "Game/General/Cloud.h"
#include "Game/General/EventInfo.h"

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
	controllers[GameParticle::WhiteSmog] = new Effect::Game::WhiteSmogController();
	controllers[GameParticle::ColorfulDebis] = new Effect::Game::ColorfulDebrisController();
	controllers[GameParticle::ExplosionFlare] = new Effect::Game::ExplosionFlareController();
	controllers[GameParticle::AngryFace] = new Effect::Game::AngryFaceController();
	controllers[GameParticle::TownExplosion] = new Effect::Game::TownExplosionController();
	controllers[GameParticle::MeteorExplosion] = new Effect::Game::MeteorExplosionController();
	controllers[GameParticle::Darkness] = new Effect::Game::DarknessController();
	controllers[GameParticle::LinkLevelUp] = new Effect::Game::LinkLevelUpController();
	controllers[GameParticle::Cloud] = new Effect::Game::CloudController();
	controllers[GameParticle::EventInfo] = new Effect::Game::EventInfoEffectController();

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
	Debug::Text("Cloud : %d", controllers[GameParticle::Cloud]->GetParticleCount());
	Debug::End();
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