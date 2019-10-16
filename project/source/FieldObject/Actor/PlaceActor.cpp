//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.cpp]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PlaceActor.h"
#include "State/CreateActorState.h"
#include "../../../Framework/Tool/DebugWindow.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 PlaceActor::ActorScale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// �R���X�g���N�^
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel) :
	state(NULL), current(), type()
{
	// ���b�V���R���e�i�̍쐬
	mesh = MeshContainer::Create();

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_RELEASE(mesh);
	state = NULL;
}

//=====================================
// �X�V
//=====================================
PlaceActor::State PlaceActor::Update()
{
	State next = Idle;

	// ��Ԃ̍X�V
	if (state != NULL)
	{
		next = state->OnUpdate(*this);
	}

#if _DEBUG
	Debug();
#endif

	return next;
}

//=====================================
// �`��
//=====================================
void PlaceActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y����]
//=====================================
void PlaceActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// �X�e�[�g�̐؂�ւ�
//=====================================
void PlaceActor::ChangeState(ActorState *next)
{
	state = next;
	state->OnStart(*this);
}

//=====================================
// ���b�V���f�[�^�̃J���[�ύX
//=====================================
void PlaceActor::SetColor(const D3DXCOLOR& color, UINT index)
{
	mesh->SetMaterialColor(color, index);
}

void PlaceActor::Debug()
{
	Debug::Begin("PlaceActor", false);
	Debug::Text("State = %d\n", current);
	Debug::End();
}