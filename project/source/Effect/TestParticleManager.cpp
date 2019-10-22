//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[TestParticleManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TestParticleManager.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "Game/BlueSpark.h"
#include "Game/BlueDebris.h"
#include "Game\WhiteSmog.h"

/**************************************
����������
***************************************/
void TestParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(TestParticle::Max, NULL);
	controllers[TestParticle::BlueSpark] = new Effect::Game::BlueSparkController();
	controllers[TestParticle::BlueDebris] = new Effect::Game::BlueDebrisController();
	controllers[TestParticle::WhiteSmog] = new Effect::Game::WhiteSmogController();
}

/**************************************
�X�V����
***************************************/
void TestParticleManager::Update()
{
	Debug::Begin("ParticleTest");

	if (Debug::Button("BlueSpark"))
		Generate(TestParticle::BlueSpark, Vector3::Up * 10.0f);
	else if (Debug::Button("BlueDebris"))
		Generate(TestParticle::BlueDebris, Vector3::Up * 10.0f);
	else if (Debug::Button("WhiteSmog"))
		Generate(TestParticle::WhiteSmog, Vector3::Up * 10.0f);

	Debug::NewLine();

	if (Debug::Button("BlueSparkDeblis"))
	{
		Generate(TestParticle::BlueSpark, Vector3::Up * 10.0f);
		Generate(TestParticle::BlueDebris, Vector3::Up * 10.0f);
	}

	Debug::End();

	SceneParticleManager::Update();
}

/**************************************
�`�揈��
***************************************/
void TestParticleManager::Draw()
{
	SceneParticleManager::Draw();

	Debug::Begin("PartcileProfile");
	for (unsigned i = 0; i < controllers.size(); i++)
	{
		Debug::Text("particle[%d] : %d", i, controllers[i]->GetParticleCount());
	}
	Debug::End();
}
