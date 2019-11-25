//=====================================
//
// �u���b�W�A�N�^�[[BridgeActor.cpp]
// �@�\�F���i���[�v�z�[���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _BRIDGEACTOR_H_
#define _BRIDGEACTOR_H_

#include "PlaceActor.h"
//**************************************
// �}�N����`
//**************************************
namespace Field::Actor
{
	class RiverEffect;
}

//**************************************
// �N���X��`
//**************************************
class BridgeActor :
	public PlaceActor
{
public:
	BridgeActor();
	~BridgeActor();

	virtual void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	virtual void Update() override;
	virtual void Draw() override;

private:
	Field::Actor::RiverEffect *effect;
	D3DXVECTOR2 uv;
	Field::FieldLevel level;
};

#endif
