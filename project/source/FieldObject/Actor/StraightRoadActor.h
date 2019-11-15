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
class BaseEmitter;

//**************************************
// �N���X��`
//**************************************
class StraightRoadActor :
	public PlaceActor
{
public:
	StraightRoadActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~StraightRoadActor();

	void Rotate(float y) override;

private:
	BaseEmitter * emitter;
};

#endif
