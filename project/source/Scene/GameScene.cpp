//=====================================
//
//GameScene.cpp
//�@�\:�Q�[���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../GameConfig.h"
#include "../../Framework/Transition/TransitionController.h"
#include "../../Framework/Core/SceneManager.h"

#include "../../Framework/Renderer3D/SkyBox.h"
#include "../FieldObject/Actor/PlaceActor.h"
#include "../Field/FieldController.h"
#include "../Field/Camera/FieldCamera.h"
#include "../../Framework/Renderer2D/TextViewer.h"
#include "../Viewer/GameScene/GameViewer/GameViewer.h"
#include "../Event/EventController.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/GameParticleManager.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "GameState/GameFinish.h"
#include "GameState/GameLevelUp.h"

#include "../FieldObject/Actor/BridgeActor.h"

#include "../../Framework/Tool/DebugWindow.h"

/**************************************
static�����o
***************************************/
int GameScene::level = 0;		//�f�o�b�O�p�t�B�[���h���x���i�{�Ԃł͔�static�����o�ɂ���

/**************************************
����������
***************************************/
void GameScene::Init()
{
	//�J�����쐬
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);

	//�e�L�X�g�p�Ƀt�H���g�����[�h
	TextViewer::LoadFont("data/FONT/mplus-2c-heavy.ttf");

	//�e�C���X�^���X�쐬
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));
	field = new Field::FieldController();
	text = new TextViewer("M+ 2c heavy", 50);
	gameViewer = new GameViewer();
	eventController = new EventController(Field::Model::City);
	eventController->ReceiveFieldController(field);
	particleManager = GameParticleManager::Instance();

	//�X�e�[�g�}�V���쐬
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();
	fsm[State::Finish] = new GameFinish();
	fsm[State::LevelUp] = new GameLevelUp();

	//�f���Q�[�g���쐬���Đݒ�
	onBuildRoad = Delegate<GameScene, Route&>::Create(this, &GameScene::OnBuildRoad);
	field->SetCallbackOnBuildRoad(onBuildRoad);

	//�X�e�[�g������
	ChangeState(State::Initialize);

	//testActor = new BridgeActor(D3DXVECTOR3(150.0f, 0.0f, -150.0f), FModel::City);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	//�J�����폜
	SAFE_DELETE(fieldCamera);

	//�t�H���g���A���C���X�g�[��
	TextViewer::RemoveFont("data/FONT/mplus-2c-heavy.ttf");

	//�C���X�^���X�폜
	SAFE_DELETE(skybox);
	SAFE_DELETE(field);
	SAFE_DELETE(text);
	SAFE_DELETE(gameViewer);
	SAFE_DELETE(eventController);

	//�p�[�e�B�N���I��
	particleManager->Uninit();

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);

	//SAFE_DELETE(testActor);
	//�f���Q�[�g�폜
	SAFE_DELETE(onBuildRoad);

}
#include "../../Framework/Camera/CameraTranslationPlugin.h"
/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	//�X�e�[�g���X�V
	State next = fsm[currentState]->OnUpdate(*this);

	if (next != currentState)
	{
		ChangeState(next);
	}

	Debug::Begin("Camera");
	if(Debug::Button("Translation")) Camera::TranslationPlugin::Instance()->Move(Vector3::Zero, 30);
	if (Debug::Button("Restore")) Camera::TranslationPlugin::Instance()->Restore(30);
	Debug::End();

	//�J�����X�V
	fieldCamera->Update();

	//�r���[���p�����[�^���r���[���ɓn��
	GameViewerParam param;
	param.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(param);
	gameViewer->ReceiveParam(param);

	//�r���A�[�X�V
	gameViewer->Update();

	//�p�[�e�B�N���X�V
	particleManager->Update();
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	//�J�����Z�b�g
	fieldCamera->Set();

	//�w�i�`��
	skybox->Draw();

	//testActor->Draw();

	//�I�u�W�F�N�g�`��
	field->Draw();

	// �C�x���g�`��
	eventController->Draw();

	//�p�[�e�B�N���`��
	particleManager->Draw();

	//�e�L�X�g�r���[�����e�X�g�\��
	static int x = 1650;
	static int y = 950;
	static std::string str = "�C�x���g�����I";
	text->SetText(str);
	text->SetPos(x, y);
	text->Draw();

	//�r���A�[�`��
	gameViewer->Draw();
}

/**************************************
�X�e�[�g�J�ڏ���
***************************************/
void GameScene::ChangeState(State next)
{
	prevState = currentState;

	currentState = next;

	if (fsm[currentState] != NULL)
	{
		fsm[currentState]->OnStart(*this);
	}
}

/**************************************
�C�x���g�R���g���[���ւ�Place�󂯓n������
***************************************/
void GameScene::OnBuildRoad(Route& route)
{
	eventController->CheckEventHappen(route, Field::Model::FieldLevel::City);
}

/**************************************
���x���A�b�v����
***************************************/
void GameScene::OnLevelUp()
{
	//�e�X�g�Ȃ̂ŃC���N�������g���Ă��܂�
	//�{�Ԃł͂����Ɛ�������
	
	TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
	{
		level++;
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	});
}
