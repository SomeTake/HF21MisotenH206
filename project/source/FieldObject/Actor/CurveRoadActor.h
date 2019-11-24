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
class BaseEmitter;

//**************************************
// �N���X��`
//**************************************
class CurveRoadActor :
	public PlaceActor
{
public:
	CurveRoadActor();
	~CurveRoadActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater);
	void Uninit() override;
	void Draw() override;
	void Rotate(float y);

private:
	std::vector<BaseEmitter*> emitterContainer;
	bool onWater;
};

#endif
