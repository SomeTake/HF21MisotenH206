//=====================================
//
// �p�b�Z���W���[�A�N�^�[[PassengerActor.h]
// �@�\�F�t�B�[���h����s��������A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PassengerActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../Field/PlaceActorController.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 PassengerActor::ActorScale = Vector3::One;
const D3DXVECTOR3 PassengerActor::InitForward = Vector3::Back;

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
// �ړI�n�ւ̈ړ�
//=====================================
void PassengerActor::MoveDest(const D3DXVECTOR3 dest, std::function<void(void)> callback)
{
	this->dest = dest;
	D3DXVECTOR3 pos = transform->GetPosition();

	// �����������ꏊ�ւ̃x�N�g��
	D3DXVECTOR3 vec = pos - this->dest;

	// �ړ��t���[��
	int frame = int(D3DXVec3Length(&vec) / Field::Actor::PlaceActorController::PlacePositionOffset) * 15;

	if (Vector3::Angle(vec, transform->Forward()) >= 90.0f)
	{
		// ���������킹�Ă���ړ�
		Tween::Turn(*this, vec, 30, Linear, Vector3::Up, [=]
		{
			Tween::Move(*this, pos, this->dest, frame, Linear, callback);
		});
	}
	else
	{
		Tween::Move(*this, pos, this->dest, frame, Linear, callback);
	}
}