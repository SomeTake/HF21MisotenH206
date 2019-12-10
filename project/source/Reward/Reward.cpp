//=====================================
//
// �����[�h[Reward.h]
// �@�\�F�e�����[�h�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "Reward.h"
#include "../Viewer/NameViewer/Name.h"

//=====================================
// �R���X�g���N�^
//=====================================
Reward::Reward(RC::Type type, int maxdata) :
	type(type), achieve(false), firstAchieve(false), name(), MaxData(maxdata)
{
	name = new Name();
}

//=====================================
// �f�X�g���N�^
//=====================================
Reward::~Reward()
{
	SAFE_DELETE(name);
}

//=====================================
// ���O�̃Z�b�g
//=====================================
void Reward::SetName(const Name& name)
{
	this->name = new Name(name);
	firstAchieve = true;
}

//=====================================
// ���O�̎擾
//=====================================
Name* Reward::GetName()
{
	return name;
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
