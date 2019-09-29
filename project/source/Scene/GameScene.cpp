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

/**************************************
����������
***************************************/
void GameScene::Init()
{
	object = new TransformObject();

	//�J�����̈ʒu��������

}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(object);
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
	object->Draw();
	Debug::Log("CurrentScene:Game");
}
