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
	vector<PlaceActor*> actor;

public:
	PlaceActor();
	~PlaceActor();
	void Update();
	void Draw();

};

#endif

