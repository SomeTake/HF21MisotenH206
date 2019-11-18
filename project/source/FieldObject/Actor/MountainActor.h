//=====================================
//
// �}�E���e���A�N�^�[[MountainActor.h]
// �@�\�F�R�i�Q���A�u���b�N�z�[���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _MOUNTAINACTOR_H_
#define _MOUNTAINACTOR_H_

#include "PlaceActor.h"
//**************************************
// �}�N����`
//**************************************
namespace Field::Actor
{
	class WhirlPoolEffect;
}

//**************************************
// �N���X��`
//**************************************
class MountainActor :
	public PlaceActor
{
public:
	MountainActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater);
	~MountainActor();

	void Update() override;
	void Draw() override;

private:
	Field::Actor::WhirlPoolEffect *effect;
	float speedWhirl;
	float cntWhirl;
};

#endif
