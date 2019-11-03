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
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../../Framework/Camera/CameraShakePlugin.h"
#include "../../../Framework/PostEffect/BloomController.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{
	// 3D�I�u�W�F�N�g�̃��\�[�X�����[�h
	ResourceManager::Instance()->LoadMesh("NoneActor", "data/MODEL/PlaceActor/ground.x");

	// �C�x���g�p���f��
	ResourceManager::Instance()->LoadMesh("Meteor", "data/MODEL/Planet/Meteor.x");

	// FieldLevel = City
	ResourceManager::Instance()->LoadMesh("CrossJunction-City", "data/MODEL/PlaceActor/Cross-Junction.x");
	ResourceManager::Instance()->LoadMesh("TJunction-City", "data/MODEL/PlaceActor/T-Junction.x");
	ResourceManager::Instance()->LoadMesh("StraightRoad-City", "data/MODEL/PlaceActor/Straight.x");
	ResourceManager::Instance()->LoadMesh("CurveRoad-City", "data/MODEL/PlaceActor/Curve.x");
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
	ResourceManager::Instance()->LoadMesh("Bridge-City", "data/MODEL/PlaceActor/bridge.x");
	ResourceManager::Instance()->LoadMesh("Mountain-City", "data/MODEL/PlaceActor/mountain.x");
	ResourceManager::Instance()->LoadMesh("River-City", "data/MODEL/PlaceActor/river.x");
	ResourceManager::Instance()->LoadMesh("Car", "data/MODEL/PassengerActor/ToonCar.x");
	ResourceManager::Instance()->LoadMesh("AlongCity", "data/MODEL/AlongActor/AlongActorCity.x");

	// FieldLevel = World

	// FieldLevel = Space

	//�p�[�e�B�N��������
	entity.particleManager->Init();

	//�J�����Ƀv���O�C����ǉ����ď�����
	entity.fieldCamera->AddPlugin(Camera::TranslationPlugin::Instance());
	entity.fieldCamera->AddPlugin(Camera::ShakePlugin::Instance());
	Camera::TranslationPlugin::Instance()->Init();

	//�J�����̒Ǐ]�ڕW�ɃJ�[�\����ݒ肵�ă��[�h�ؑ�
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

	//CSV�f�[�^�����[�h
	entity.field->Load();

	//�C�x���g�n���h���ݒ�
	entity.SetEventHandler();

	//�u���[���G�t�F�N�g�̃p�����[�^�ݒ�
	entity.bloomController->SetPower(entity.BloomPower[0], entity.BloomPower[1], entity.BloomPower[2]);
	entity.bloomController->SetThrethold(entity.BloomThrethold[0], entity.BloomThrethold[1], entity.BloomThrethold[2]);

	//�������ԓǂݍ���
	//TODO:�V�[�����ׂ��ň����p���悤�ɂ���
	entity.remainTime = 30 * 180;

	//�g�����W�V������ʂ��I�t�ɂ��đJ��
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]()
	{
		entity.ChangeState(State::Idle);
	});
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameInit::OnUpdate(GameScene & entity)
{
	return GameScene::State::Initialize;
}
