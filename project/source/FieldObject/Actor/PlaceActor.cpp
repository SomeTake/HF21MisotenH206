//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.cpp]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PlaceActor.h"
#include "State/CreateActorState.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 PlaceActor::ActorScale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// �R���X�g���N�^
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
{
	// ���b�V���R���e�i�̍쐬
	mesh = MeshContainer::Create();

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(pos);
	transform->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	this->SetActive(true);

	// state = NULL;

	state = new CreateActorState();
	state->OnStart(*this);
}

//=====================================
// �f�X�g���N�^
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// �X�V
//=====================================
PlaceActor::State PlaceActor::Update()
{
	// ��Ԃ̍X�V
	return state->OnUpdate(*this);

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