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
#include "../Framework/Core/PlayerPrefs.h"

#include "GameConfig.h"

#include "Scene\GameScene.h"
#include "Scene/ParticleTestScene.h"
#include "Scene/ModelViewScene.h"
#include "Scene\MophingTestScene.h"

/**************************************
�R���X�g���N�^
***************************************/
GameMain::GameMain(HINSTANCE hInstance, HWND hWnd) :
	BaseGame(hInstance, hWnd)
{
	//�V�[���}�l�[�W���ɃV�[���̃C���X�^���X��ǉ�
	sceneManager->Add(GameConfig::SceneID::Game, new GameScene(renderTexture, renderSurface));
	sceneManager->Add(GameConfig::SceneID::ParticleTest, new ParticleTestScene(renderTexture, renderSurface));
	sceneManager->Add(GameConfig::SceneID::ModelView, new ModelViewScene(renderTexture, renderSurface));
	sceneManager->Add(GameConfig::SceneID::MophingTest, new MophingTestScene(renderTexture, renderSurface));

	//�^�C�g�����܂������̂ł����Ńp�����[�^�����������Ă��܂�
	PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_RemainTime), 30 * 180);
	PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), 0);

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
	else if (Debug::Button("ModelView"))
		sceneManager->ChangeScene(GameConfig::ModelView);
	else if (Debug::Button("Mophing"))
		sceneManager->ChangeScene(GameConfig::MophingTest);

	Debug::End();
}