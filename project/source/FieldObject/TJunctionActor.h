//=====================================
//
// T�W�����N�V�����A�N�^�[[TJunctionActor.h]
// �@�\�FT���H3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _TJUNCTIONACTOR_H_
#define _TJUNCTIONACTOR_H_

#include "PlaceActor.h"
//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class TJunctionActor :
	public PlaceActor
{
public:
	TJunctionActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~TJunctionActor();

	void Update()override;
};

#endif
