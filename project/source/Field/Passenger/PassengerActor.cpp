//=====================================
//
// �p�b�Z���W���[�A�N�^�[[PassengerActor.h]
// �@�\�F�t�B�[���h����s��������A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PassengerActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 PassengerActor::ActorScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

//=====================================
// �R���X�g���N�^
//=====================================
PassengerActor::PassengerActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
{
	mesh = MeshContainer::Create();

	// ���x���ɍ��킹�ă��f���ǂݍ���
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("Car", mesh);
		break;
	case FModel::World:
		ResourceManager::Instance()->GetMesh("Train", mesh);
		break;
	case FModel::Space:
		ResourceManager::Instance()->GetMesh("Rocket", mesh);
		break;
	default:
		break;
	}

	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
PassengerActor::~PassengerActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// �X�V
//=====================================
void PassengerActor::Update()
{
	if (!this->IsActive())
		return;
}

//=====================================
// �`��
//=====================================
void PassengerActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// ���b�V���̐؂�ւ�
//=====================================
void PassengerActor::ChangeMesh(const char* nextTag)
{
	mesh = NULL;
	ResourceManager::Instance()->GetMesh(nextTag, mesh);
}

//=====================================
// �ړ�
//=====================================
void PassengerActor::Move()
{

}