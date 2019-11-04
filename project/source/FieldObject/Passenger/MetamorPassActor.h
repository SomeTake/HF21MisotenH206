//=====================================
//
// ���^�����p�X�A�N�^�[[MetamorPassActor.h]
// �@�\�F�t�B�[���h����s��������A�N�^�[�i�����x���Ŏg�p�B���f�������I�ɐ؂�ւ��j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _METAMORPASSACTOR_H_
#define _METAMORPASSACTOR_H_

#include "PassengerActor.h"

//**************************************
// �N���X��`
//**************************************
class MetamorPassActor :
	public PassengerActor
{
private:
	Field::FieldPosition fieldPos;	// �t�B�[���h��̍��W

	// ���b�V���̏�Ԃ�\���X�e�[�g
	enum State
	{
		Ship,
		Train,
	};
	State current;					// ���݂̃��b�V���̏��
	bool change;					// ���b�V���؂�ւ��t���O

	void CheckState();

public:
	MetamorPassActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~MetamorPassActor();

	void Update()override;

	Field::FieldPosition FieldPosition();	// �t�B�[���h��̍��W��Ԃ�
	void SetChange(bool flag);				// �@���b�V���؂�ւ��t���O�̃Z�b�g
};

#endif
