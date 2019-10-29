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
#include "../Viewer/GameScene/GameViewer/GameViewer.h"
#include "../Event/EventController.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/GameParticleManager.h"
#include "../Field/FieldEventHandler.h"

#include "../../Framework/PostEffect/BloomController.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "GameState/GameFinish.h"
#include "GameState/GameLevelUp.h"
#include "GameState\/GamePause.h"

#include "../../Framework/Tool/DebugWindow.h"

/**************************************
static�����o
***************************************/
int GameScene::level = 0;		//�f�o�b�O�p�t�B�[���h���x���i�{�Ԃł͔�static�����o�ɂ���
const float GameScene::BloomPower[] = {0.25f, 0.25f, 0.15f};		//�u���[���̋���
const float GameScene::BloomThrethold[] = {0.45f, 0.5f, 0.55f};		//�u���[����������P�x��臒l

/**************************************
����������
***************************************/
void GameScene::Init()
{
	//�J�����쐬
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);

	//�e�C���X�^���X�쐬
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));
	field = new Field::FieldController();
	gameViewer = new GameViewer();
	eventController = new EventController(Field::Model::City);
	eventHandler = new FieldEventHandler();
	eventController->ReceiveFieldEventHandler(eventHandler);
	particleManager = GameParticleManager::Instance();
	bloomController = new BloomController();

	//�X�e�[�g�}�V���쐬
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();
	fsm[State::Finish] = new GameFinish();
	fsm[State::LevelUp] = new GameLevelUp();
	fsm[State::Pause] = new GamePause();

	//�f���Q�[�g���쐬���Đݒ�
	onBuildRoad = DelegateObject<GameScene, void(Route&)>::Create(this, &GameScene::OnBuildRoad);
	field->SetCallbackOnBuildRoad(onBuildRoad);

	//�X�e�[�g������
	ChangeState(State::Initialize);

	//testActor = new CityActor(D3DXVECTOR3(150.0f, 0.0f, -150.0f), FModel::City);
	std::vector<D3DXVECTOR3> root;
	D3DXVECTOR3 push = D3DXVECTOR3(150.0f, 0.0f, -150.0f);
	root.push_back(push);
	push = D3DXVECTOR3(250.0f, 0.0f, -150.0f);
	root.push_back(push);
	push = D3DXVECTOR3(250.0f, 0.0f, -50.0f);
	root.push_back(push);
	push = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	root.push_back(push);
	passengerController = new PassengerController();
	passengerController->SetPassenger(root);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	//�J�����폜
	SAFE_DELETE(fieldCamera);

	//�C���X�^���X�폜
	SAFE_DELETE(skybox);
	SAFE_DELETE(field);
	SAFE_DELETE(gameViewer);
	SAFE_DELETE(eventController);
	SAFE_DELETE(bloomController);

	//�p�[�e�B�N���I��
	particleManager->Uninit();

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);

	//SAFE_DELETE(testActor);
	SAFE_DELETE(passengerController);

	//�f���Q�[�g�폜
	SAFE_DELETE(onBuildRoad);

}

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

	//�J�����X�V
	fieldCamera->Update();

	//testActor->Update();
	passengerController->Update();

	//�r���[���p�����[�^���r���[���ɓn��
	GameViewerParam param;
	param.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(param);
	gameViewer->ReceiveParam(param);

	//�r���A�[�X�V
	gameViewer->Update();

	//�p�[�e�B�N���X�V
	particleManager->Update();

	Debug::Begin("EventHandler");
	if (Debug::Button("Pause"))
		eventHandler->PauseGame();
	if (Debug::Button("Resume"))
		eventHandler->ResumeGame();
	if (Debug::Button("GetTownPos"))
		eventHandler->GetNewTownPosition();
	if (Debug::Button("DestroyTown"))
		eventHandler->DestroyTown(eventHandler->GetDestroyTarget());
	Debug::End();
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
	passengerController->Draw();

	//�I�u�W�F�N�g�`��
	field->Draw();

	// �C�x���g�I�u�W�F�N�g�`��
	eventController->DrawEventObject();

	//�|�X�g�G�t�F�N�g�͏d���̂Ń����[�X�ł̂ݓK�p����
#ifndef _DEBUG
	//�|�X�g�G�t�F�N�g�K�p
	bloomController->Draw(renderTexture);
#endif
	//�p�[�e�B�N���`��
	particleManager->Draw();

	// �C�x���g�r���[�A�`��
	eventController->DrawEventViewer();

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

/**************************************
�C�x���g�n���h���ݒ菈��
***************************************/
void GameScene::SetEventHandler()
{
	//���f�t�@���N�^�쐬
	eventHandler->functerVoid[FieldEventHandler::FuncterID_void::Pause] = [&]()
	{
		ChangeState(State::Pause);
	};

	//�ĊJ�t�@���N�^�쐬
	eventHandler->functerVoid[FieldEventHandler::FuncterID_void::Resume] = [&]()
	{
		//TODO:���f�O�̃X�e�[�g�֖߂��悤�ɂ���
		ChangeState(State::Idle);
	};

	//�������ԉ񕜃t�@���N�^�쐬
	eventHandler->functerInt[FieldEventHandler::FuncterID_int::AddTime] = [&](int frame)
	{
		this->remainTime += frame;
	};

	//�t�B�[���h�R���g���[���̕��ł��n���h���쐬
	field->SetEventHandler(*eventHandler);
}
