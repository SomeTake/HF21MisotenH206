//=====================================
//
// �J�E���g�A�b�v�����[�h[CountupReward.cpp]
// �@�\�F�J�E���g�A�b�v����^�C�v�̃����[�h
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CountupReward.h"

//=====================================
// �R���X�g���N�^
//=====================================
CountupReward::CountupReward(RC::Type type, int maxdata) :
	Reward(type, maxdata), data(0)
{
}

//=====================================
// �f�X�g���N�^
//=====================================
CountupReward::~CountupReward()
{
}

//=====================================
// �f�[�^�̃Z�b�g
//=====================================
void CountupReward::SetData(int data)
{
	if (this->data < MaxData)
	{
		this->data += data;
		if (this->data >= MaxData)
		{
			achieve = true;
		}
	}
}

//=====================================
// �f�[�^�̃��Z�b�g
//=====================================
void CountupReward::ResetData()
{
	data = 0;
	achieve = false;
}

