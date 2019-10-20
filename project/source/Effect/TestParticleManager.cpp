//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[TestParticleManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TestParticleManager.h"
#include "Game/BlueSpark.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
����������
***************************************/
void TestParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(TestParticle::Max, NULL);
	controllers[TestParticle::BlueSpark] = new Effect::Game::BlueSparkController();
}

/**************************************
�X�V����
***************************************/
void TestParticleManager::Update()
{
	Debug::Begin("ParticleTest");

	if (Debug::Button("BlueSpark"))
		Generate(TestParticle::BlueSpark, Vector3::Up * 10.0f);

	Debug::End();

	SceneParticleManager::Update();
}
