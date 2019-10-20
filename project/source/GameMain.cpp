//=====================================
//
//GameMain.cpp
//�@�\:�Q�[�����C������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameMain.h"
#include "../Framework/Core/SceneManager.h"
#include "../Framework/Tool/DebugWindow.h"

#include "GameConfig.h"

#include "Scene\GameScene.h"
#include "Scene/ParticleTestScene.h"

/**************************************
�R���X�g���N�^
***************************************/
GameMain::GameMain(HINSTANCE hInstance, HWND hWnd) :
	BaseGame(hInstance, hWnd)
{
	//�V�[���}�l�[�W���ɃV�[���̃C���X�^���X��ǉ�
	sceneManager->Add(GameConfig::SceneID::Game, new GameScene());
	sceneManager->Add(GameConfig::SceneID::ParticleTest, new ParticleTestScene());

	//�����V�[���ɑJ��
	const int InitScene = GameConfig::SceneID::Game;
	sceneManager->ChangeScene(InitScene);
}

/**************************************
�X�V����
***************************************/
void GameMain::Update()
{
	BaseGame::Update();

	Debug::Begin("Scene");

	if (Debug::Button("Game"))
		sceneManager->ChangeScene(GameConfig::Game);
	else if (Debug::Button("ParticleTest"))
		sceneManager->ChangeScene(GameConfig::ParticleTest);

	Debug::End();

}
