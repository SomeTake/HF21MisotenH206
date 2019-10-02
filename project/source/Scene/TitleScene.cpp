//=====================================
//
//TitleScene.cpp
//�@�\:�^�C�g���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TitleScene.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
����������
***************************************/
void TitleScene::Init()
{
	//�J�����쐬
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);
}

/**************************************
�I������
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
}

/**************************************
�X�V����
***************************************/
void TitleScene::Update()
{
}

/**************************************
�`�揈��
***************************************/
void TitleScene::Draw()
{
	Debug::Log("CurrentScene:Title");
}
