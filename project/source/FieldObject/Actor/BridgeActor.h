//=====================================
//
// �u���b�W�A�N�^�[[BridgeActor.cpp]
// �@�\�F���i���[�v�z�[���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _BRIDGEACTOR_H_
#define _BRIDGEACTOR_H_

#include "PlaceActor.h"
//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class BridgeActor :
	public PlaceActor
{
public:
	BridgeActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~BridgeActor();
};

#endif
