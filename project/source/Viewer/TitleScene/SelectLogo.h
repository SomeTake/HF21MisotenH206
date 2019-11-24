//=====================================
//
// �Z���N�g���S[SelectLogo.h]
// �@�\�F�Z���N�g���S
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _SELECTLOGO_H_
#define _SELECTLOGO_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "SelectViewer.h"

//**************************************
// �N���X��`
//**************************************
class SelectLogo :
	BillboardObject
{
private:
	BoardPolygon* polygon;

	// �ړ�����
	bool moveRight;
	bool moveLeft;
	int counter;
	float angle;

	bool Moveable();	// ����\����

	// �X�^�e�B�b�N�����o
	static const float Distance;
	static const int MoveFrame;

public:
	SelectLogo();
	~SelectLogo();

	void Update();
	void Draw();

	void LoadResource(const char* tag);
	void SetPosition(const D3DXVECTOR3& pos);
	void SetTexDiv(const D3DXVECTOR2& div);
	void SetTextureIndex(const int& index);
	void TurnRight();	// �E�Ɉړ�
	void TurnLeft();	// ���Ɉړ�
	void SetAngle(float angle);

	// ���Z�q�̃I�[�o�[���[�h
	// �`�揇�\�[�g�̂���
	bool operator < (const SelectLogo& another)const
	{
		return transform->GetPosition().z < another.transform->GetPosition().z;
	}
	bool operator > (const SelectLogo& another)const
	{
		return transform->GetPosition().z > another.transform->GetPosition().z;
	}

	// �X�^�e�B�b�N�����o
	static const D3DXVECTOR3 InitLogoPos[SelectViewer::Mode::Max];
};

#endif
