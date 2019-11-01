//=====================================
//
// �C���t�H�f�B�W�b�g[InfoDigit.h]
// �@�\�F���\���p����
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _INFODIGIT_H_
#define _INFODIGIT_H_

#include "../../../Framework/Renderer2D/Polygon2D.h"
//**************************************
// �N���X��`
//**************************************
class InfoDigit :
	public Polygon2D
{
private:
	int num;

	static const int divideX, divideY;	// ������
	static const float width, height;	// ���A����

public:
	InfoDigit(const int& num, const D3DXVECTOR3& pos);
	~InfoDigit();

	void Update();

	// �\�����鐔���̕ύX
	void ChangeDigit(const int& num);
};

#endif
