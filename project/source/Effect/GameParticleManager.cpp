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
	controllers.resize(ParticleID::Max, NULL);
	controllers[BlueSpark] = new Effect::Game::BlueSparkController();
}
