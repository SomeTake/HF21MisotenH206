//=====================================
//
// ���^�����p�X�A�N�^�[[MetamorPassActor.cpp]
// �@�\�F�t�B�[���h����s��������A�N�^�[�i�����x���Ŏg�p�B���f�������I�ɐ؂�ւ��j
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "MetamorPassActor.h"

//=====================================
// �R���X�g���N�^
//=====================================
MetamorPassActor::MetamorPassActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel) :
	PassengerActor(pos, currentLevel)
{
	current = Ship;
	fieldPos = Field::FieldPosition::ConvertToFieldPosition(transform->GetPosition());
	change = false;
}

//=====================================
// �f�X�g���N�^
//=====================================
MetamorPassActor::~MetamorPassActor()
{
}

//=====================================
// �X�V
//=====================================
void MetamorPassActor::Update()
{
	if (!IsActive())
		return;

	// ���b�V���؂�ւ��m�F
	CheckState();
}

//=====================================
// �X�e�[�g�̊m�F
//=====================================
void MetamorPassActor::CheckState()
{
	if (change)
	{
		if (current == Ship)
		{
			ChangeMesh("Train-World");
		}
		else if (current == Train)
		{
			ChangeMesh("Ship-Train");
		}
	}
}

//=====================================
// �t�B�[���h��̍��W��Ԃ�
//=====================================
Field::FieldPosition MetamorPassActor::FieldPosition()
{
	return fieldPos = Field::FieldPosition::ConvertToFieldPosition(transform->GetPosition());
}

//=====================================
// ���b�V���؂�ւ��t���O�̃Z�b�g
//=====================================
void MetamorPassActor::SetChange(bool flag)
{
	change = flag;
}