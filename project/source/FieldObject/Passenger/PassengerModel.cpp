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
PassengerModel::PassengerModel(const std::deque<D3DXVECTOR3>& root, std::function<void(const D3DXVECTOR3&)> *callback) :
	callbackToAlong(callback)
{
	this->root = root;
	// ���ƂŃt�H�[���h���x���𔽉f������
	actor = new PassengerActor(this->root[0], FModel::City);
	nextDest = 1;
	actor->MoveDest(this->root[nextDest], [=]
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
	root.clear();
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
	//(*callbackToAlong)(root[nextDest]);

	// �ړI�n�ɓ��B���Ă��邩�m�F
	if ((size_t)nextDest >= root.size() - 1)
	{
		actor->SetActive(false);
		return;
	}

	// ���̖ړI�n�փZ�b�g
	nextDest++;
	actor->MoveDest(root[nextDest], [=]
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
void PassengerModel::SetActor(const std::deque<D3DXVECTOR3>& root)
{
	this->root = root;
	// ���ƂŃt�H�[���h���x���𔽉f������
	actor->SetActive(true);
	actor->SetPosition(this->root[0]);
	nextDest = 1;
	actor->MoveDest(this->root[nextDest], [=]
	{
		CheckCallback();
	});
}