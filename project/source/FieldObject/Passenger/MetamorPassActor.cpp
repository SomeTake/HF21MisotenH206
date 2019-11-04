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

}

//=====================================
// �f�X�g���N�^
//=====================================
MetamorPassActor::~MetamorPassActor()
{
}

//=====================================
// ���[���h���W����PlaceModel�̍��W�ɕϊ�����
//=====================================
Field::FieldPosition MetamorPassActor::ConvertToFieldPosition()
{
	D3DXVECTOR3 pos = transform->GetPosition();
	Field::FieldPosition ret;

	ret.x = (int)pos.x / 10;
	ret.z = abs((int)pos.z / 10);

	return ret;
}
