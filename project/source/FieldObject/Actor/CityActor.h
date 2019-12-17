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
// �O���錾
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

	void StartMorph(int next);

	static const int DurationMorphing;

private:
	MorphingMeshContainer * morphContainer;		//���[�t�B���O�p���b�V���R���e�i
	
	bool useMorphing;							//���[�t�B���O���g�p���邩�ǂ���
	bool inMorphing;							//���[�t�B���O�����ǂ���

	int cntFrameMorphing;						//���[�t�B���O���̃J�E���^
	int currentMorphing;						//���݂̃��[�t�B���O�C���f�b�N�X
};

#endif
