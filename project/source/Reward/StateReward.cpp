//=====================================
//
// �X�e�[�g�����[�h[StateReward.cpp]
// �@�\�F�������̏�Ԃ��m�F����^�C�v�̃����[�h
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "StateReward.h"

//=====================================
// �R���X�g���N�^
//=====================================
StateReward::StateReward(RewardController::Type type, int maxdata) :
	Reward(type, maxdata)
{
	for (int i = 0; i < MaxData; i++)
	{
		data.push_back(0);
	}
}

//=====================================
// �f�X�g���N�^
//=====================================
StateReward::~StateReward()
{
	data.clear();
}

//=====================================
// �f�[�^�̃Z�b�g
//=====================================
void StateReward::SetData(int data)
{
	this->data[data] = 1;

}

//=====================================
// �f�[�^�̃��Z�b�g
//=====================================
void StateReward::ResetData()
{
	for (auto& i : data)
	{
		i = 0;
	}
}