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
#include "../../../Framework/Renderer3D/Viewer3D.h"

//**************************************
// �N���X��`
//**************************************
class InfoActor :
	public BillboardObject
{
protected:
	Viewer3D* viewer;	// 3D�\������

	static const D3DXVECTOR2 ViewerWorldSize;
	static const DWORD ViewerCanvasSize;

public:
	InfoActor(const D3DXVECTOR3& pos);
	virtual ~InfoActor();

	// �X�V�A�`��p�������z�֐�
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
#endif