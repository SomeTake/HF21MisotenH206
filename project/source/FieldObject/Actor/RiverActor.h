//=====================================
//
// ���o�[�A�N�^�[[RiverActor.h]
// �@�\�F��i����f��j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _RIVERACTOR_H_
#define _RIVERACTOR_H_

#include "PlaceActor.h"
//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class RiverActor :
	public PlaceActor
{
public:
	RiverActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~RiverActor();
};

#endif
