//=====================================
//
// �����[�h[Reward.h]
// �@�\�F�e�����[�h�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "Reward.h"

//=====================================
// �R���X�g���N�^
//=====================================
Reward::Reward(RewardController::Type type, int maxdata) :
	type(type), achieve(false), firstAchieve(false), name(), MaxData(maxdata)
{
}

//=====================================
// �f�X�g���N�^
//=====================================
Reward::~Reward()
{
}

//=====================================
// ���O�̃Z�b�g
//=====================================
void Reward::SetName(int BuffNo, int AlphabetNo)
{
	this->name[BuffNo] = AlphabetNo;
}

//=====================================
// ���O�̎擾
//=====================================
int Reward::GetName(int BuffNo)
{
	return this->name[BuffNo];
}

//=====================================
// �B���m�F
//=====================================
bool Reward::CheckAchieved()
{
	return this->achieve;
}

//=====================================
// �B���m�F
//=====================================
bool Reward::CheckFirstAchieved()
{
	return this->firstAchieve;
}

//=====================================
// �B���̃��Z�b�g
//=====================================
void Reward::ResetAchieved()
{
	this->achieve = false;
}
