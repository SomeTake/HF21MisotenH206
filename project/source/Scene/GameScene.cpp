//=====================================
//
//GameScene.cpp
//�@�\:�Q�[���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../../Framework/Renderer3D/SkyBox.h"
#include "../FieldObject/Actor/PlaceActor.h"
#include "../Field/FieldController.h"
#include "../Field/Camera/FieldCamera.h"
#include "../../Framework/Renderer2D/TextViewer.h"
#include "../Viewer/GameScene/GameViewer/GameViewer.h"
#include "../Event/EventController.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"

//���C�x���g�R���g���[���[���o�����炻�����ړ�
#include "../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../FieldObject/Actor/CrossJunctionActor.h"
#include "../FieldObject/Actor/BridgeActor.h"

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

	//�X�e�[�g�}�V���쐬
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();

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

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);

	//SAFE_DELETE(testActor);
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

	//�r���[���p�����[�^���r���[���ɓn��
	GameViewerParam param;
	param.remainTime = remainTime / 30.0f;
	field->EmbedViewerParam(param);
	gameViewer->ReceiveParam(param);

	//�r���A�[�X�V
	gameViewer->Update();

	//testActor->Update();
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

	//�e�L�X�g�r���[�����e�X�g�\��
	static int x = 1650;
	static int y = 950;
	static std::string str = "�C�x���g�����I";
	text->SetText(str);
	text->SetPos(x, y);
	text->Draw();

	//�r���A�[�`��
	gameViewer->Draw();

	// �C�x���g�`��
	eventController->Draw();
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
