//=====================================
//
//GameScene.cpp
//�@�\:�Q�[���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../../Framework/Renderer3D/TransformObject.h"
#include "../../Framework/Renderer3D/SkyBox.h"

/**************************************
����������
***************************************/
void GameScene::Init()
{
	object = new TransformObject();
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));

	//�X�J�C�{�b�N�X�̃e�N�X�`�������[�h
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_up.png", SkyBox::Surface::Up);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_back.png", SkyBox::Surface::Back);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_down.jpg", SkyBox::Surface::Down);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_front.png", SkyBox::Surface::Front);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_left.png", SkyBox::Surface::Left);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_right.png", SkyBox::Surface::Right);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(object);
	SAFE_DELETE(skybox);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{

}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	skybox->Draw();

	object->Draw();
	Debug::Log("CurrentScene:Game");
}
