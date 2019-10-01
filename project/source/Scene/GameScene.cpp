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
#include "../Field/FieldController.h"

#include "GameState/GameInit.h"
#include "GameState\GameIdle.h"

/**************************************
����������
***************************************/
void GameScene::Init()
{
	//�e�C���X�^���X�쐬
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));
	field = new FieldModel::FieldController();

	//�X�e�[�g�}�V���쐬
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();

	//�X�e�[�g������
	ChangeState(State::Initialize);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	//�C���X�^���X�폜
	SAFE_DELETE(skybox);

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	State next = fsm[currentState]->OnUpdate(*this);

	if (next != currentState)
	{
		ChangeState(next);
	}
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	//�w�i�`��
	skybox->Draw();

	//�I�u�W�F�N�g�`��
	field->Draw();
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
