//=====================================
//
// �X�R�A[Score.h]
// �@�\�F�X�R�A�Ǘ��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "../../main.h"
#include "../Field/FieldController.h"

//**************************************
// �N���X��`
//**************************************
namespace Field
{
	class Score
	{
	private:
		FieldLevel current;	// ���݂̃t�B�[���h���x��
		UINT developmentLevelAI;	// ��AI���W���x�����X�R�A

	public:
		Score();
		~Score();

		UINT GetScore();			// �X�R�A�̎擾
		void AddScore(UINT score, FieldLevel current);	// �X�R�A�̉��Z
	};
}

#endif
