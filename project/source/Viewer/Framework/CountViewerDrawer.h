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
	//�z�b�s���O�֘A�ϐ�
	void HopNumber(float numSizeY);
	bool isHopped;
	float radian;
	float hopValue = 30.0f;
	float hopSpeed = 0.20f;
	float initSizeNumY = 15.0f;

	void DrawCounter(int baseNumber, int parameterBox, int placeMax,
		float intervalNumberScr, float intervalNumberTex);

	//�p�����[�^���󂯂Ƃ锠
	int parameterBox;

	//�X�N���[����̕\���Ԋu
	float intervalNumberScr;

	//�e�N�X�`���f�ނ̂̕\���Ԋu
	float intervalNumberTex;

	//����
	int placeMax;

	//�i���@
	int baseNumber;

private:
	void SetVertex(int placeCount, float placeInterval);
	void SetTexture(int number, float placeInterval);

};

#endif

