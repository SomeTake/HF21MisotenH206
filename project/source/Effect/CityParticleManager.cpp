//=====================================
//
//CityParticleManager.cpp
//�@�\:�X���x���̃p�[�e�B�N���}�l�[�W��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "CityParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Particle/BaseParticleController.h"

#include "Game/City/BlueSpark.h"
#include "Game/City/BlueDebris.h"

/**************************************
static�����o
***************************************/
const float CityParticleManager::BloomPower[3] = { 1.0f, 1.0f, 1.0f };
const float CityParticleManager::BloomThrethold[3] = { 0.46f, 0.35f, 0.18f };

/**************************************
����������
***************************************/
void CityParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(CityParticle::Max, NULL);
	controllers[CityParticle::BlueSpark] = new Effect::Game::BlueSparkController();
	controllers[CityParticle::BlueDebris] = new Effect::Game::BlueDebrisController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
�V���M�������e�B�G�t�F�N�g�Z�b�g����
***************************************/
void CityParticleManager::SetSingularityEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	const D3DXVECTOR3 OffsetPosition = Vector3::Up * 10.0f;

	//BlueDebris�̕��̕��o���Ԃ��������߂ɂ��Ă���̂ŁABlueDebris�ɃR�[���o�b�N��ݒ肷��
	controllers[CityParticle::BlueSpark]->SetEmitter(position + OffsetPosition);
	controllers[CityParticle::BlueDebris]->SetEmitter(position + OffsetPosition, callback);
}
