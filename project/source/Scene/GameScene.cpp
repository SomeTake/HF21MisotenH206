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
#include "../../Framework/Core/PlayerPrefs.h"
#include "../../Framework/Serial/SerialWrapper.h"
#include "../../Framework/Network/UDPClient.h"
#include "../../Framework/Network/PacketConfig.h"

#include "../GameConfig.h"
#include "../Field/Object/FieldSkyBox.h"
#include "../FieldObject/Actor/PlaceActor.h"
#include "../Field/FieldController.h"
#include "../Field/Camera/FieldCamera.h"
#include "../Viewer/GameScene/Controller/GameViewer.h"
#include "../Event/EventController.h"
#include "../Field/Place/PlaceConfig.h"
#include "../Effect/GameParticleManager.h"
#include "../Field/FieldEventHandler.h"
#include "../Effect/CityParticleManager.h"
#include "../Effect/WorldParticleManager.h"
#include "../Effect/SpaceParticleManager.h"
#include "../Viewer/GameScene/GuideViewer/GuideViewer.h"

#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Effect/SpriteEffect.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "GameState/GameFinish.h"
#include "GameState/GameLevelUp.h"
#include "GameState/GamePause.h"
#include "GameState/GameFarView.h"
#include "GameState/GameTitle.h"
#include "GameState/GameResult.h"
#include "GameState\GameTransitionOut.h"
#include "GameState\GameTransitionIn.h"

#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Sound/BackgroundMusic.h"

/**************************************
static�����o
***************************************/
int GameScene::level = 0;		//�f�o�b�O�p�t�B�[���h���x���i�{�Ԃł͔�static�����o�ɂ���
const float GameScene::BloomPower[] = {0.6f, 0.55f, 0.50f};		//�u���[���̋���
const float GameScene::BloomThrethold[] = {0.6f, 0.5f, 0.4f};		//�u���[����������P�x��臒l

/**************************************
����������
***************************************/
void GameScene::Init()
{
	//�J�����쐬
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);

	//�t�B�[���h���x���ǂݍ���
	Field::FieldLevel level = (Field::FieldLevel)PlayerPrefs::GetNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel));

	//�e�C���X�^���X�쐬
	field = new Field::FieldController(level);
	gameViewer = new GameViewer();
	eventController = new EventController(level);
	eventHandler = new FieldEventHandler();
	eventController->ReceiveFieldEventHandler(eventHandler);
	particleManager = GameParticleManager::Instance();
	bloomController = new BloomController();
	//serial = new SerialWrapper(3);								//TODO:�|�[�g�ԍ���ς�����悤�ɂ���
	Client = new UDPClient();
	guideViewer = new GuideViewer();

	//���x�����̃p�[�e�B�N���}�l�[�W����I��
	switch (level)
	{
	case Field::City:
		levelParticleManager = CityParticleManager::Instance();
		break;
	case Field::World:
		levelParticleManager = WorldParticleManager::Instance();
		break;

	case Field::Space:
		levelParticleManager = SpaceParticleManager::Instance();
		break;
	default:
		levelParticleManager = nullptr;
		break;
	}

	//�X�e�[�g�}�V���쐬
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();
	fsm[State::Finish] = new GameFinish();
	fsm[State::LevelUp] = new GameLevelUp();
	fsm[State::Pause] = new GamePause();
	fsm[State::FarView] = new GameFarView();
	fsm[State::Title] = new GameTitle();
	fsm[State::Result] = new GameResult();
	fsm[State::TransitionOut] = new GameTransitionOut();
	fsm[State::TransitionIn] = new GameTransitionIn();

	//�f���Q�[�g���쐬���Đݒ�
	auto onBuildRoad = std::bind(&GameScene::OnBuildRoad, this, std::placeholders::_1);
	field->SetCallbackBuildRoad(onBuildRoad);

	//�X�e�[�g������
	ChangeState(State::Initialize);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	//�J�����폜
	SAFE_DELETE(fieldCamera);

	//�C���X�^���X�폜
	SAFE_DELETE(field);
	SAFE_DELETE(gameViewer);
	SAFE_DELETE(eventController);
	SAFE_DELETE(bloomController);
	SAFE_DELETE(eventHandler);
	//SAFE_DELETE(serial);
	SAFE_DELETE(Client);
	SAFE_DELETE(guideViewer);

	//�p�[�e�B�N���I��
	particleManager->Uninit();

	if(levelParticleManager != nullptr)
		levelParticleManager->Uninit();

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);
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

	//�r���[���p�����[�^���r���[���ɓn��
	GameViewerParam gameParam;
	gameParam.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(gameParam);
	gameViewer->ReceiveParam(gameParam);

	EventViewerParam eventParam;
	eventController->EmbedViewerParam(eventParam);

	//�r���A�[�X�V
	gameViewer->Update();
	guideViewer->Update();

	//�p�[�e�B�N���X�V
	ProfilerCPU::Instance()->Begin("Update Particle");

	if(levelParticleManager != nullptr)
		levelParticleManager->Update();

	particleManager->Update();

	ProfilerCPU::Instance()->End("Update Particle");

	//�f�o�b�O�@�\
	DebugTool();

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
	Camera::MainCamera()->Set();

	//�I�u�W�F�N�g�`��
	ProfilerCPU::Instance()->Begin("Draw Object");
	field->Draw();
	ProfilerCPU::Instance()->End("Draw Object");

	// �C�x���g�I�u�W�F�N�g�`��
	ProfilerCPU::Instance()->Begin("Draw Event");
	eventController->DrawEventObject();
	ProfilerCPU::Instance()->End("Draw Event");

	//testInfoController->Draw();

	//�|�X�g�G�t�F�N�g�͏d���̂Ń����[�X�ł̂ݓK�p����
#ifndef _DEBUG
	//�|�X�g�G�t�F�N�g�K�p
	ProfilerCPU::Instance()->Begin("Draw PostEffect");
	bloomController->Draw(renderTexture);
	ProfilerCPU::Instance()->End("Draw PostEffect");
#endif

	//�t�B�[���h�̏��\��
	field->DrawInfo();

	//�p�[�e�B�N���`��
	ProfilerCPU::Instance()->Begin("Draw Particle");
	
	if(levelParticleManager != nullptr)
		levelParticleManager->Draw();

	particleManager->Draw();
	ProfilerCPU::Instance()->End("Draw Particle");

	//�r���A�[�`��
	field->DrawViewer();
	gameViewer->Draw();
	eventController->DrawEventViewer();

	//*******�ʃE�C���h�E���쐬���邽�ߍŌ�*******
	guideViewer->Draw();

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
	bool flgPause = eventController->CheckEventHappen(route, Field::FieldLevel::City);

	if (flgPause)
		ChangeState(State::Pause);
}

/**************************************
���x���A�b�v����
***************************************/
void GameScene::OnLevelUp()
{
	//���݂̐������Ԃ�ۑ�
	PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_RemainTime), remainTime);

	//BGM���t�F�[�h�A�E�g
	BGM::Fade(0.0f, 30, true);

	//�e�X�g�Ȃ̂ŃC���N�������g���Ă��܂�
	//�{�Ԃł͂����Ɛ�������
	level++;
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

/**************************************
�f�o�b�O�@�\
***************************************/
void GameScene::DebugTool()
{
	//�f�o�b�O�@�\
	Debug::Begin("DebugTool");
	Debug::Text("Level");
	if (Debug::Button("CityLevel"))
	{
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), Field::FieldLevel::City);
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	}
	Debug::SameLine();
	if (Debug::Button("WorldLevel"))
	{
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), Field::FieldLevel::World);
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	}
	Debug::SameLine();
	if (Debug::Button("SpaceLevel"))
	{
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), Field::FieldLevel::Space);
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	}

	Debug::NewLine();
	if (Debug::Button("All Reset"))
	{
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_FieldLevel), Field::FieldLevel::City);
		PlayerPrefs::SaveNumber<int>(Utility::ToString(GameConfig::Key_RemainTime), 30 * 180);
		SceneManager::ChangeScene(GameConfig::SceneID::Game);
	}

	Debug::NewLine();
	if (Debug::Button("Add Time"))
	{
		remainTime += 30 * 10;
	}

	Debug::NewLine();
	if (Debug::Button("SendPacket"))
	{
		PacketConfig Packet;
		GameViewerParam gameParam;
		field->EmbedViewerParam(gameParam);
		Packet.AILevel = gameParam.levelAI;
		Client->ReceivePacketConfig(Packet);
		Client->SendPacket();
	}

	Debug::Text("State");
	Debug::NewLine();
	if (Debug::Button("Title"))
	{
		level = 0;
		ChangeState(State::Title);
	}
	Debug::SameLine();
	if (Debug::Button("Idle"))
	{
		level = 1;
		ChangeState(State::Idle);
	}
	Debug::SameLine();
	if (Debug::Button("Result"))
	{
		level = 2;
		ChangeState(State::Result);
	}
	Debug::SameLine();
	if (Debug::Button("Transition"))
	{
		level++;
		ChangeState(State::TransitionOut);
	}

	Debug::NewLine();
	Debug::Text("Bloom");
	static D3DXVECTOR3 power = {BloomPower[0], BloomPower[1], BloomPower[2]};
	static D3DXVECTOR3 threthold = {BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]};
	Debug::Slider("power", power, Vector3::Zero, Vector3::One);
	Debug::Slider("threthold", threthold, Vector3::Zero, Vector3::One);
	bloomController->SetPower(power.x, power.y, power.z);
	bloomController->SetThrethold(threthold.x, threthold.y, threthold.z);

	Debug::End();
}

/**************************************
�t�B�[���h���x���ݒ菈��
***************************************/
void GameScene::SetFieldLevel(int level)
{
	LARGE_INTEGER start, end;

	//�t�B�[���h���x����ݒ�
	field->SetLevel((Field::FieldLevel)level);

	//���x���ŗL�̃p�[�e�B�N���}�l�[�W��������
	start = ProfilerCPU::GetCounter();
	switch (level)
	{
	case Field::City:
		levelParticleManager = CityParticleManager::Instance();
		break;
	case Field::World:
		levelParticleManager = WorldParticleManager::Instance();
		break;
	case Field::Space:
		levelParticleManager = SpaceParticleManager::Instance();
		break;
	default:
		levelParticleManager = nullptr;
		break;
	}
	levelParticleManager->Init();

	end = ProfilerCPU::GetCounter();

	Debug::Log("Init Particle : %f", ProfilerCPU::CalcElapsed(start, end));

	start = ProfilerCPU::GetCounter();

	//�C�x���g�R���g���[���쐬
	eventController->Init(level);

	//�C�x���g�n���h���ݒ�
	SetEventHandler();

	end = ProfilerCPU::GetCounter();

	Debug::Log("Init Event : %f", ProfilerCPU::CalcElapsed(start, end));
}

/**************************************
�V�[���N���A����
***************************************/
void GameScene::Clear()
{
	LARGE_INTEGER start, end;

	//�t�B�[���h�����N���A
	start = ProfilerCPU::GetCounter();
	field->Clear();
	end = ProfilerCPU::GetCounter();

	Debug::Log("Clear Field : %f", ProfilerCPU::CalcElapsed(start, end));

	//���x���ŗL�̃p�[�e�B�N�����I��
	start = ProfilerCPU::GetCounter();
	levelParticleManager->Uninit();
	levelParticleManager = nullptr;
	end = ProfilerCPU::GetCounter();

	Debug::Log("Clear Particle : %f", ProfilerCPU::CalcElapsed(start, end));

	//�C�x���g�R���g���[���N���A
	start = ProfilerCPU::GetCounter();
	eventController->Uninit();
	end = ProfilerCPU::GetCounter();

	Debug::Log("Clear Event : %f", ProfilerCPU::CalcElapsed(start, end));
}
