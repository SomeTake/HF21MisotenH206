//=====================================
//
// ���^�����p�X�A�N�^�[[MetamorPassActor.h]
// �@�\�F�t�B�[���h����s��������A�N�^�[�i�����x���Ŏg�p�B���f�������I�ɐ؂�ւ��j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _METAMORPASSACTOR_H_
#define _METAMORPASSACTOR_H_

#include "PassengerActor.h"

//**************************************
// �N���X��`
//**************************************
class MetamorPassActor :
	public PassengerActor
{

public:
	MetamorPassActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~MetamorPassActor();

};

#endif
