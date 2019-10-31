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
#include "../../../Framework/Renderer2D/Polygon2D.h"
#include "../../../Framework/Renderer3D/Viewer3D.h"

//**************************************
// �N���X��`
//**************************************
class DigitInfo :
	public Polygon2D
{
private:
	int num;

public:
	DigitInfo(const int& num, const D3DXVECTOR3& pos);
	~DigitInfo();

	void Update();
};

class InfoActor :
	public BillboardObject
{
protected:
	Viewer3D* viewer;	// 3D�\������
	DigitInfo* digit[2];
	int linkLevel;

	static const float ActorSize;

public:
	InfoActor(const D3DXVECTOR3& pos);
	virtual ~InfoActor();

	// �X�V�A�`��
	virtual void Update();
	virtual void Draw();
};
#endif