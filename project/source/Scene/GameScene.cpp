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
#include "../../Framework/Tool/ProfilerCPU.h"

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
#include "../../Framework/Effect/SpriteEffect.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "GameState/GameFinish.h"
#include "GameState/GameLevelUp.h"
#include "GameState/GamePause.h"
#include "GameState\GameFarView.h"

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
	fsm[State::FarView] = new GameFarView();

	//�f���Q�[�g���쐬���Đݒ�
	onBuildRoad = DelegateObject<GameScene, void(Route&)>::Create(this, &GameScene::OnBuildRoad);
	field->SetCallbackOnBuildRoad(onBuildRoad);

	//�X�e�[�g������
	ChangeState(State::Initialize);

	// �e�X�g�p
	//testActor = new CityActor(D3DXVECTOR3(150.0f, 0.0f, -150.0f), FModel::City);
	//std::vector<D3DXVECTOR3> root;
	//D3DXVECTOR3 push = D3DXVECTOR3(150.0f, 0.0f, -150.0f);
	//root.push_back(push);
	//push = D3DXVECTOR3(250.0f, 0.0f, -150.0f);
	//root.push_back(push);
	//push = D3DXVECTOR3(250.0f, 0.0f, -50.0f);
	//root.push_back(push);
	//push = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	//root.push_back(push);
	//passengerController = new PassengerController();
	//passengerController->SetPassenger(root);
	//testInfo = new LinkInfoActor(D3DXVECTOR3(160.0f, 0.0f, -160.0f), 85);
	//testInfoController = new InfoController();
	//testInfoController->SetLinkLevel(Field::FieldPosition(16, 16), 100);
	//testInfoController->SetLinkLevel(Field::FieldPosition(17, 17), 90);
	//testInfoController->SetLinkLevel(Field::FieldPosition(29, 29), 99);
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
	SAFE_DELETE(eventHandler);

	//�p�[�e�B�N���I��
	particleManager->Uninit();

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);

	// �e�X�g�p
	//SAFE_DELETE(testActor);
	//SAFE_DELETE(passengerController);
	//SAFE_DELETE(testInfo);
	//SAFE_DELETE(testInfoController);

	//�f���Q�[�g�폜
	SAFE_DELETE(onBuildRoad);

}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	ProfilerCPU::Instance()->BeginLabel("GameScene");

	//�X�e�[�g���X�V
	State next = fsm[currentState]->OnUpdate(*this);

	//�J�����X�V
	ProfilerCPU::Instance()->Begin("Update Camera");
	fieldCamera->Update();
	ProfilerCPU::Instance()->End("Update Camera");

	//�J�����̏����G�t�F�N�g�ɓn��
	SpriteEffect::SetView(fieldCamera->GetViewMtx());
	SpriteEffect::SetProjection(fieldCamera->GetProjectionMtx());

	// �e�X�g�p
	//testActor->Update();
	//passengerController->Update();
	//testInfo->Update();
	//testInfoController->Update();

	//�r���[���p�����[�^���r���[���ɓn��
	GameViewerParam param;
	param.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(param);
	gameViewer->ReceiveParam(param);

	//�r���A�[�X�V
	gameViewer->Update();

	//�p�[�e�B�N���X�V
	ProfilerCPU::Instance()->Begin("Update Particle");
	particleManager->Update();
	ProfilerCPU::Instance()->End("Update Particle");

	Debug::Begin("EventHandler");
	if (Debug::Button("Pause"))
		eventHandler->PauseGame();
	if (Debug::Button("Resume"))
		eventHandler->ResumeGame();
	if (Debug::Button("GetTownPos"))
		eventHandler->GetNewTownPosition();
	if (Debug::Button("DestroyTown"))
		eventHandler->DestroyTown(eventHandler->GetDestroyTarget());
	if (Debug::Button("CreateTown"))
		eventHandler->CreateNewTown(eventHandler->GetNewTownPosition());
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

	// �e�X�g�p
	//testActor->Draw();
	//passengerController->Draw();

	//�I�u�W�F�N�g�`��
	ProfilerCPU::Instance()->Begin("Draw Object");
	field->Draw();
	ProfilerCPU::Instance()->End("Draw Object");

	// �C�x���g�I�u�W�F�N�g�`��
	ProfilerCPU::Instance()->Begin("Draw Event");
	eventController->DrawEventObject();
	ProfilerCPU::Instance()->End("Draw Event");
	//testInfo->Draw();
	//testInfoController->Draw();

	//�|�X�g�G�t�F�N�g�͏d���̂Ń����[�X�ł̂ݓK�p����
#ifndef _DEBUG
	//�|�X�g�G�t�F�N�g�K�p
	ProfilerCPU::Instance()->Begin("Draw PostEffect");
	bloomController->Draw(renderTexture);
	ProfilerCPU::Instance()->End("Draw PostEffect");
#endif

	//�p�[�e�B�N���`��
	ProfilerCPU::Instance()->Begin("Draw Particle");
	particleManager->Draw();
	ProfilerCPU::Instance()->End("Draw Particle");

	// �C�x���g�r���[�A�`��
	eventController->DrawEventViewer();

	//�r���A�[�`��
	gameViewer->Draw();

	ProfilerCPU::Instance()->EndLabel();
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
