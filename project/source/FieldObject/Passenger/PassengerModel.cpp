//=====================================
//
// �p�b�Z���W���[���f��[PassengerModel.cpp]
// �@�\�F�p�b�Z���W���[�̃��f���N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PassengerModel.h"

//=====================================
// �R���X�g���N�^
//=====================================
PassengerModel::PassengerModel(const std::deque<D3DXVECTOR3>& root, Field::FieldLevel level, std::function<void(const D3DXVECTOR3&)> *callback) :
	current(0),
	nextDest(0),
	callbackToAlong(callback)
{
	this->route = root;

	actor = new PassengerActor(this->route[0], level);
	D3DXVECTOR3 destination = FindDestination();
	actor->MoveDest(destination, [=]
	{
		CheckCallback();
	});
}

//=====================================
// �f�X�g���N�^
//=====================================
PassengerModel::~PassengerModel()
{
	SAFE_DELETE(actor);
	route.clear();
}

//=====================================
// �X�V
//=====================================
void PassengerModel::Update()
{
	actor->Update();
}

//=====================================
// �`��
//=====================================
void PassengerModel::Draw()
{
	actor->Draw();
}

//=====================================
// �R�[���o�b�N�̊m�F
//=====================================
void PassengerModel::CheckCallback()
{
	//�������̃��f���R���g���[���փA�N�^�[�������������W��n��
	for (int i = current; i <= nextDest; i++)
	{
		(*callbackToAlong)(route[i]);
	}

	// �ړI�n�ɓ��B���Ă��邩�m�F
	if ((size_t)nextDest >= route.size() - 1)
	{
		actor->SetActive(false);
		return;
	}

	// ���̖ړI�n�փZ�b�g
	current = nextDest;
	D3DXVECTOR3 destination = FindDestination();
	actor->MoveDest(destination, [=]
	{
		CheckCallback();
	});
}

//=====================================
// �g�p���m�F
//=====================================
bool PassengerModel::IsActive()
{
	return actor->IsActive();
}

//=====================================
// �A�N�^�[�̃Z�b�g
//=====================================
void PassengerModel::SetActor(const std::deque<D3DXVECTOR3>& root, Field::FieldLevel level)
{
	this->route = root;

	switch (level)
	{
	case Field::City:
		if (actor->GetType() != PassengerActor::Car)
		{
			ChangeMesh("Car");
		}
		break;
	case Field::World:
		if (actor->GetType() != PassengerActor::Train)
		{
			ChangeMesh("Train");
		}
		break;
	case Field::Space:
		if (actor->GetType() != PassengerActor::SpaceShip)
		{
			ChangeMesh("SpaceShip");
		}
		break;
	default:
		break;
	}

	// ���ƂŃt�B�[���h���x���𔽉f������
	actor->SetActive(true);
	actor->SetPosition(this->route[0]);
	this->current = nextDest = 0;
	actor->MoveDest(this->route[nextDest], [=]
	{
		CheckCallback();
	});
}

//=====================================
// �A�N�^�[�̖ړI�n��T��
//=====================================
D3DXVECTOR3 PassengerModel::FindDestination()
{
	D3DXVECTOR3 position = route[current];
	D3DXVECTOR3 offset = route[current + 1] - position;

	unsigned i = current;
	for (; i < route.size() - 1; i++, nextDest++)
	{
		D3DXVECTOR3 next = position + offset * (i + 1.0f - current);

		//�Ȃ���p�ɏo���킷�܂Ō�������
		if (!Vector3::Equal(next, route[i + 1]))
		{
			return route[i];
		}
	}

	nextDest = route.size() - 1;
	return route.back();
}

//=====================================
// �A�N�^�[�̍��W���t�B�[���h���W�ɕϊ����ĕԂ�
//=====================================
Field::FieldPosition PassengerModel::GetFieldPosition()
{
	return Field::FieldPosition::ConvertToFieldPosition(actor->GetPosition());
}

//=====================================
// �A�N�^�[�̃��b�V���ύX
//=====================================
void PassengerModel::ChangeMesh(const char* tag)
{
	actor->ChangeMesh(tag);
}

//=====================================
// �A�N�^�[�̌��݂̃��b�V���̏�Ԃ��擾
//=====================================
PassengerActor::State PassengerModel::GetType()
{
	return actor->GetType();
}

//=====================================
// �A�N�^�[�̃^�O��ύX
//=====================================
void PassengerModel::SetType(PassengerActor::State next)
{
	actor->SetType(next);
}