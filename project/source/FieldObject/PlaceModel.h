//=====================================
//
// �v���C�X���f��[PlaceModel.h]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g���Ǘ�����N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PLACEMODEL_H_
#define _PLACEMODEL_H_

#include <vector>

//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class PlaceActor;
class PlaceModel
{
private:
	std::vector<PlaceActor*> actor;

public:
	PlaceModel();
	~PlaceModel();
	void Update();
	void Draw();

};

#endif

