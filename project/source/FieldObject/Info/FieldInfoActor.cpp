//=====================================
//
// �t�B�[���h�C���t�H�A�N�^�[[FieldInfoActor.cpp]
// �@�\�F�t�B�[���h��̏���\������A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "FieldInfoActor.h"
#include "CreateFieldInfoState.h"
#include "IdleFieldInfoState.h"
#include "RemoveFieldInfoState.h"
#include "ConnectFieldInfoState.h"
#include "LinkFieldInfoState.h"
#include "CongestionFieldInfoState.h"

#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 FieldInfoActor::ActorScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
const D3DXVECTOR2 FieldInfoActor::ActorSize = D3DXVECTOR2(2.0f, 2.0f);

//=====================================
// �R���X�g���N�^
//=====================================
FieldInfoActor::FieldInfoActor(const D3DXVECTOR3& pos, State state)
{
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);

	// �r���{�[�h�쐬
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("Info", polygon);

	// �X�e�[�g�}�V���쐬
	fsm.resize(State::Max, NULL);
	fsm[State::Idle] = new IdleFieldInfoState();
	fsm[State::Create] = new CreateFieldInfoState();
	fsm[State::Remove] = new RemoveFieldInfoState();
	fsm[State::Connect] = new ConnectFieldInfoState();
	fsm[State::Link] = new LinkFieldInfoState();
	fsm[State::Congestion] = new CongestionFieldInfoState();

	// �X�e�[�g������
	this->ChangeState(state);
}

//=====================================
// �f�X�g���N�^
//=====================================
FieldInfoActor::~FieldInfoActor()
{
	SAFE_DELETE(polygon);

	// �X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);
}

//=====================================
// ����������
//=====================================
void FieldInfoActor::Init()
{
	ResourceManager::Instance()->MakePolygon("Info", "data/TEXTURE/Info/Info.png", ActorSize);
}

//=====================================
// �X�V
//=====================================
void FieldInfoActor::Update()
{
	if (!this->IsActive())
		return;;

	// ���݂̃X�e�[�g�X�V
	State next = infoState->OnUpdate(*this);
	if (next != current)
	{
		ChangeState(next);
	}
}

//=====================================
// �`��
//=====================================
void FieldInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	polygon->Draw();

}

//=====================================
// �X�e�[�g�}�V���̐؂�ւ�
//=====================================
void FieldInfoActor::ChangeState(State next)
{
	if (fsm[next] == NULL)
		return;

	current = next;
	infoState = fsm[next];
	infoState->OnStart(*this);
}