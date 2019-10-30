//=====================================
//
// �����N�C���t�H�A�N�^�[[LinkInfoActor.h]
// �@�\�F���̃����N���x����\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _LINKINFOACTOR_H_
#define _LINKINFOACTOR_H_

#include "InfoActor.h"

//**************************************
// �N���X��`
//**************************************
class LinkInfoActor :
	public InfoActor
{
private:
	static const int MaxDigit = 2;
	DigitActor* digit[MaxDigit];

public:
	LinkInfoActor(const D3DXVECTOR3& pos, const int& level);
	~LinkInfoActor();

	// �X�V�A�`��
	void Update()override;
	void Draw()override;
};

class DigitActor :
	public BillboardObject
{
private:
	BoardPolygon* polygon;
	int num;				// �\�����鐔��

public:
	DigitActor(int num);
	~DigitActor();

	void Update();
	void Draw();
};

#endif

