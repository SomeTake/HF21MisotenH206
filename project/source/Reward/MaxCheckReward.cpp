//=====================================
//
// �}�b�N�X�`�F�b�N�����[�h[MaxCheckReward.h]
// �@�\�F�ő�l�𒴂������m�F����^�C�v�̃����[�h
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "MaxCheckReward.h"

//=====================================
// �R���X�g���N�^
//=====================================
MaxCheckReward::MaxCheckReward(RC::Type type, int maxdata) :
	Reward(type, maxdata), data(0)
{
}

//=====================================
// �f�X�g���N�^
//=====================================
MaxCheckReward::~MaxCheckReward()
{
}

//=====================================
// �f�[�^�̍X�V
//=====================================
void MaxCheckReward::SetData(int data)
{
	this->data = data;
	if (data >= MaxData)
	{
		achieve = true;
	}
}

//=====================================
// �f�[�^�̃��Z�b�g
//=====================================
void MaxCheckReward::ResetData()
{
	this->data = 0;
	achieve = false;
}