//=====================================
//
// �X�g���[�g���[�h�A�N�^�[[StraightRoadActor.cpp]
// �@�\�F�܂������ȓ��p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _STRAIGHTROADACTOR_H_
#define _STRAIGHTROADACTOR_H_

#include "PlaceActor.h"
//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class StraightRoadActor :
	public PlaceActor
{
public:
	StraightRoadActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~StraightRoadActor();

	void Update()override;
};

#endif
