//=============================================================================
//
// �J�E���g�r���A�[�`�揈�� [CountViewerDrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COUNT_VIEWER_DRAWER_H_
#define _COUNT_VIEWER_DRAWER_H_

#include "BaseViewerDrawer.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CountViewerDrawer :public BaseViewerDrawer
{
public:
	void DrawCounter(int baseNumber, int parameterBox, int placeMax,
		float intervalNumberScr, float intervalNumberTex);

	//�X�N���[����̕\���Ԋu
	float intervalNumberScr;

	//�e�N�X�`���f�ނ̂̕\���Ԋu
	float intervalNumberTex;

	//����
	int placeMax;

	//�i���@
	int baseNumber;

	//�z�b�v�A�j���[�V�����֘A�ϐ�
	float HopNumber(float sizeY, float initSizeY, float hopValue);
	bool isHopped;
	float radian;
	const float hopSpeed = D3DX_PI/10;

private:
	void SetVertex(int placeCount, float placeInterval);
	void SetTexture(int number, float placeInterval);

};

#endif

