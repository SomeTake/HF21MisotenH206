//=============================================================================
//
// �J�E���g�r���A�[�`�揈�� [CountViewerDrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COUNT_VIEWER_DRAWER_H_
#define _COUNT_VIEWER_DRAWER_H_

#include "CountViewerDrawer.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CountViewerDrawer :public BaseViewerDrawer
{
public:
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

