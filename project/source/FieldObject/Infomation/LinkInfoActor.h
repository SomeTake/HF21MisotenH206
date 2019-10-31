//=====================================
//
// �����N�C���t�H�A�N�^�[[LinkInfoActor.h]
// �@�\�F�����N���x����\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _LINKINFOACTOR_H_
#define _LINKINFOACTOR_H_

#include "InfoActor.h"
#include "InfoDigit.h"

//**************************************
// �N���X��`
//**************************************
class LinkInfoActor :
	public InfoActor
{
private:
	static const int MaxDigit = 2;
	int linkLevel;						// �����N���x��
	int digit[MaxDigit];				// �����N���x�����ꌅ���Ƃɕ���
	InfoDigit* digitActor[MaxDigit];	// �ꌅ���Ƃɕ\��
	Polygon2D* logo;					// �����N���x���̃��S�\��

public:
	LinkInfoActor(const D3DXVECTOR3& pos, const int& level);
	~LinkInfoActor();

	// �X�V�A�`��
	void Update()override;
	void Draw()override;

	// ���x���ύX���g�p
	void SetLevel(const int& nextLevel);

};

#endif

