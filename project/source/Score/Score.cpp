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
		current(FieldLevel::City),
		score()
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
	int Score::GetScore(FieldLevel level)
	{
		return score[level];
	}

	//=====================================
	// �X�R�A�̃Z�b�g
	//=====================================
	void Score::SetScore(int score, FieldLevel current)
	{
		this->score[current] = score;
	}
}