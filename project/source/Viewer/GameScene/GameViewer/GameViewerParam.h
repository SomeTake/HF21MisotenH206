//=============================================================================
//
// �Q�[���r���A�[�p�����[�^ [GameViewerParam.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAME_VIEWER_PARAM_H_
#define _GAME_VIEWER_PARAM_H_

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class GameViewerParam
{
public:
	//AI���x��
	int levelAI;

	//���x������
	float ratioLevel;

	//�c�莞��
	float remainTime;

	//�X�g�b�N��
	int stockNum;

	// �X�g�b�N�g�p�֎~��
	bool InBanStock = false;
	// �^�C���X�g�b�v�C�x���g��
	bool InPauseEvent = false;
};

#endif