//=============================================================================
//
// ���U���g�r���A�[�p�����[�^ [ResultViewerParam.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_VIEWER_PARAM_H_
#define _RESULT_VIEWER_PARAM_H_

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultViewerParam
{
public:
	const static int fieldTypeMax = 3;

	//City�X�R�A,World�X�R�A,Space�X�R�A
	int score[fieldTypeMax] = { 0,0,0 };

	//City�ō�������̐�,World�ō�������̐��ASpace�ō�������̐�
	int builtRoad[fieldTypeMax] = { 0,0,0 };

	//City�Ōq�������X�̐�,World�Ōq�������X�̐��ASpace�Ōq�������X�̐�
	int connectedCity[fieldTypeMax] = { 0,0,0 };

	// �p�����[�^���N���A����
	void Clear(void)
	{
		for (int i = 0; i < fieldTypeMax; i++)
		{
			score[i] = 0;
			builtRoad[i] = 0;
			connectedCity[i] = 0;
		}
	}
};

#endif