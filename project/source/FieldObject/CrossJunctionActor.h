//=====================================
//
// �N���X�W�����N�V�����A�N�^�[[CrossJunctionActor.h]
// �@�\�F�\���H3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _CROSSJUNCTIONACTOR_H_
#define _CROSSJUNCTIONACTOR_H_

#include "PlaceActor.h"

//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class CrossJunctionActor :
	public PlaceActor
{
private:

public:
	CrossJunctionActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~CrossJunctionActor();
	void Update()override;
	//void Draw()override;
};

#endif
