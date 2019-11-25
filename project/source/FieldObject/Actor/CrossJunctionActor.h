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
class BaseEmitter;

//**************************************
// �N���X��`
//**************************************
class CrossJunctionActor :
	public PlaceActor
{
private:

public:
	CrossJunctionActor();
	~CrossJunctionActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater);
	void Uninit() override;
	void Draw() override;
	void Rotate(float y) override;

private:
	std::vector<BaseEmitter*> emitterContainer;
	bool onWater;
};

#endif
