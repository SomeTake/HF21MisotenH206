//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"
#include "Game/BlueSpark.h"

/**************************************
�O���[�o���ϐ�
***************************************/
void GameParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(GameParticle::Max, NULL);
	controllers[GameParticle::BlueSpark] = new Effect::Game::BlueSparkController();
}
