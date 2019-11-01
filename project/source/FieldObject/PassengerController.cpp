//=====================================
//
// �p�b�Z���W���[�R���g���[��[PassengerController.cpp]
// �@�\�F�p�b�Z���W���[�Ǘ��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PassengerController.h"
#include <algorithm>

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const int PassengerController::PassengerReserve = 1000;

//=====================================
// �R���X�g���N�^
//=====================================
PassengerController::PassengerController() :
	callback(nullptr)
{
	modelVector.reserve(PassengerReserve);
}

//=====================================
// �f�X�g���N�^
//=====================================
PassengerController::~PassengerController()
{
	for (auto& vec : modelVector)
	{
		SAFE_DELETE(vec);
	}
	modelVector.clear();
}

//=====================================
// �X�V
//=====================================
void PassengerController::Update()
{
	for (auto& actor : modelVector)
	{
		actor->Update();
	}
}

//=====================================
// �`��
//=====================================
void PassengerController::Draw()
{
	for (auto& actor : modelVector)
	{
		actor->Draw();
	}
}

//=====================================
// �p�b�Z���W���[�̃Z�b�g
//=====================================
void PassengerController::SetPassenger(std::vector<D3DXVECTOR3>& root)
{
	bool check = false;
	int sub = 0;
	// vector�̓����ɖ��g�p�̂��̂����邩�m�F
	for (auto& vec : modelVector)
	{
		if (!vec->IsActive())
		{
			check = true;
			break;
		}
		sub++;
	}

	if (check)
	{
		modelVector[sub]->SetActor(root);
	}
	else
	{
		PassengerModel *model = new PassengerModel(root, &callback);
		modelVector.push_back(model);
	}
}

//=====================================
// �R�[���o�b�N�ݒ菈��
//=====================================
void PassengerController::SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback)
{
	this->callback = callback;
}
