//=====================================
//
// �m���A�N�^�[[NoneActor.h]
// �@�\�F�����A�N�^�[���Ȃ���Ԃ�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _NONEACTOR_H_
#define _NONEACTOR_H_

#include "PlaceActor.h"

//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class NoneActor :
	public PlaceActor
{
private:
public:
	NoneActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~NoneActor();
};

#endif
