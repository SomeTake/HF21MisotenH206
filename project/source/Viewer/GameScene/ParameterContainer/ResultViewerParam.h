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
	int score[fieldTypeMax];

	//City�ŒB�����������[�h��,World�ŒB�����������[�h���ASpace�ŒB�����������[�h�̐�
	int completedRewardNum[fieldTypeMax];
};

#endif