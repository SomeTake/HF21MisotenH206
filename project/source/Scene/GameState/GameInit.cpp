//=====================================
//
//GameInit.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameInit.h"
#include "../../../Framework/Renderer3D/SkyBox.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Field/FieldController.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{
	//�X�J�C�{�b�N�X�̃e�N�X�`�������[�h
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_up.png", SkyBox::Surface::Up);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_back.png", SkyBox::Surface::Back);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_down.jpg", SkyBox::Surface::Down);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_front.png", SkyBox::Surface::Front);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_left.png", SkyBox::Surface::Left);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_right.png", SkyBox::Surface::Right);

	//�J�����̒Ǐ]�ڕW�ɃJ�[�\����ݒ肵�ă��[�h�ؑ�
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode();
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameInit::OnUpdate(GameScene & entity)
{
	return GameScene::State::Idle;
}
