//=====================================
//
// �X�R�A[Score.cpp]
// �@�\�F�X�R�A�Ǘ��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "Score.h"

namespace Field
{
	//=====================================
	// �R���X�g���N�^
	//=====================================
	Score::Score() :
		developmentLevelAI(0),
		current(FieldLevel::City)
	{
	}


	//=====================================
	// �f�X�g���N�^
	//=====================================
	Score::~Score()
	{
	}

	//=====================================
	// �X�R�A�̎擾
	//=====================================
	UINT Score::GetScore()
	{
		return developmentLevelAI;
	}

	//=====================================
	// �X�R�A�̉��Z
	//=====================================
	void Score::AddScore(UINT score, FieldLevel current)
	{
		this->current = current;
		switch (this->current)
		{
		case Field::City:
			developmentLevelAI += score;
			break;
		case Field::World:
			developmentLevelAI += score * 10000 + 9999;
			break;
		case Field::Space:
			developmentLevelAI += score * 100000000 + 99999999;
			break;
		}
	}
}
