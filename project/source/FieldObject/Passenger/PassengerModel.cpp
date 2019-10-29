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
PassengerModel::PassengerModel(const std::vector<D3DXVECTOR3>& root)
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