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
	StraightRoadActor();
	~StraightRoadActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWataer);
	void Uninit() override;
	void Draw() override;

	void Rotate(float y) override;

	void OnSea(bool state) override;

private:
	BaseEmitter * emitter;
	bool onWater;
};

#endif
