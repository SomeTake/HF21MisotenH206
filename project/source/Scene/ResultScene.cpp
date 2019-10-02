//=====================================
//
//ResultScene.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResultScene.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
����������
***************************************/
void ResultScene::Init()
{
	//�J�����쐬
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);
}

/**************************************
�I������
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
}

/**************************************
�X�V����
***************************************/
void ResultScene::Update()
{
}

/**************************************
�`�揈��
***************************************/
void ResultScene::Draw()
{
	Debug::Log("CurrenstScene:Result");
}
