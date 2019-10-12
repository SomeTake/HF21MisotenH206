//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.cpp]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PlaceActor.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 PlaceActor::ActorScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

//=====================================
// �R���X�g���N�^
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
{
	// ���b�V���R���e�i�̍쐬
	mesh = MeshContainer::Create();

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);

	state = NULL;
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