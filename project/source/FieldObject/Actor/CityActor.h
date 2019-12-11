//=====================================
//
// �V�e�B�A�N�^�[[CityActor.cpp]
// �@�\�F�s�s�i���A���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _CITYACTOR_H_
#define _CITYACTOR_H_

#include "PlaceActor.h"
//**************************************
// �}�N����`
//**************************************
class MorphingMeshContainer;

//**************************************
// �N���X��`
//**************************************
class CityActor :
	public PlaceActor
{
public:
	CityActor();
	~CityActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	MorphingMeshContainer * morphingMesh;
	bool useMorphing;

	float t;
};

#endif
