//=====================================
//
//�p�[�e�B�N���e�X�g�V�[������[ParticleTestScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ParticleTestScene.h"
#include "../../Framework/Renderer3D/SkyBox.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../Field/FieldGround.h"
#include "../Effect/TestParticleCamera.h"
#include "../FieldObject/Actor/CityActor.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/TestParticleManager.h"

/**************************************
����������
***************************************/
void ParticleTestScene::Init()
{
	//�C���X�^���X�쐬
	skybox = new SkyBox(Vector3::One * 10000.0f);
	ground = new Field::FieldGround();
	sceneCamera = new TestParticleCamera();
	particleManager = TestParticleManager::Instance();

	//�X�J�C�{�b�N�X�̃e�N�X�`�����[�h
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_up.png", SkyBox::Surface::Up);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_back.png", SkyBox::Surface::Back);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_down.jpg", SkyBox::Surface::Down);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_front.png", SkyBox::Surface::Front);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_left.png", SkyBox::Surface::Left);
	skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_right.png", SkyBox::Surface::Right);

	//�A�N�^�[�̃��f�������[�h
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
	actor = new CityActor(Vector3::Zero, Field::Model::FieldLevel::City);

	//�J�����ݒ�
	Camera::SetMainCamera(sceneCamera);

	//�p�[�e�B�N��������
	particleManager->Init();
}

/**************************************
�I������
***************************************/
void ParticleTestScene::Uninit()
{
	//�C���X�^���X�폜
	SAFE_DELETE(skybox);
	SAFE_DELETE(ground);
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(actor);

	//�p�[�e�B�N���폜
	particleManager->Uninit();
}

/**************************************
�X�V����
***************************************/
void ParticleTestScene::Update()
{
	sceneCamera->Update();

	particleManager->Update();
}

/**************************************
�`�揈��
***************************************/
void ParticleTestScene::Draw()
{
	sceneCamera->Set();

	skybox->Draw();
	ground->Draw();
	actor->Draw();

	particleManager->Draw();
}
