//=====================================
//
// �t�B�[���h�C���t�H�A�N�^�[[FieldInfoActor.h]
// �@�\�F�t�B�[���h��̏���\������A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _FIELDINFOACTOR_H_
#define _FIELDINFOACTOR_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"

//**************************************
// �N���X��`
//**************************************
class FieldInfoActor :
	public BillboardObject
{
private:
	BoardPolygon* polygon;

	static const D3DXVECTOR3 ActorScale;

public:
	FieldInfoActor(const D3DXVECTOR3& pos);
	~FieldInfoActor();

	void Update();
	void Draw();
};

#endif

