//=====================================
//
// �C���t�H�A�N�^�[[InfoActor.h]
// �@�\�F�t�B�[���h��ɏ���\�����邽�߂̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _INFOACTOR_H_
#define _INFOACTOR_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"

//**************************************
// �N���X��`
//**************************************
class InfoActor :
	public BillboardObject
{
protected:
	//*******�p����Ŏg�p********
	BoardPolygon* polygon;
	//***************************

	static const float ActorSize;

public:
	InfoActor(const D3DXVECTOR3& pos);
	virtual ~InfoActor();

	// �X�V�A�`��
	virtual void Update();
	virtual void Draw();
};

#endif