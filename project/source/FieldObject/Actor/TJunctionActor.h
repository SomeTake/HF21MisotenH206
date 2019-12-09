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
class BaseEmitter;

//**************************************
// �N���X��`
//**************************************
class TJunctionActor :
	public PlaceActor
{
public:
	TJunctionActor();
	~TJunctionActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater);
	void Uninit() override;
	void Draw() override;
	void Rotate(float y) override;

	void OnSea(bool statea) override;

private:
	std::vector<BaseEmitter*> emitterContainer;
	bool onWater;
};

#endif
