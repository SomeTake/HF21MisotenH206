//=====================================
//
// �J�[�u���[�h�A�N�^�[[CurveRoadActor.h]
// �@�\�F�J�[�u�p��3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _CURVEROADACTOR_H_
#define _CURVEROADACTOR_H_

#include "PlaceActor.h"
//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class CurveRoadActor :
	public PlaceActor
{
public:
	CurveRoadActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~CurveRoadActor();
};

#endif
