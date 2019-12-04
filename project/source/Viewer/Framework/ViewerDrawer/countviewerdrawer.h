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

	void DrawCounter(int baseNumber, int parameterBox,
		float intervalNumberScr, float intervalNumberTex);

	void DrawCounterLeft(int baseNumber, int parameterBox,
		float intervalNumberScr, float intervalNumberTex);

	//�X�N���[����̕\�����W�Ԋu
	float intervalPosScr;

	//�e�N�X�`���f�ނ̕\�����W�Ԋu
	float intervalPosTex;

	//����
	int placeMax;

	//�i���@
	int baseNumber = 10;

	//�z�b�v�A�j���[�V�����֘A�ϐ�
	float HopNumber(float sizeY, float initSizeY, float hopValue);
	bool isHopped;
	float radian;
	const float hopSpeed = D3DX_PI / 10;

	CountViewerDrawer(D3DXVECTOR2 position, D3DXVECTOR2 size, const char* path, 
		float intervalPosScr, float intervalPosTex, int placeMax);
	CountViewerDrawer();
	~CountViewerDrawer();
private:
	void Draw();

	void SetVertexPos(int placeCount, float placeInterval);
	void SetVertexPosLeft(int placeCount, float placeInterval);
	void SetTexture(int number, float placeInterval);

	int texDivX = 4;
	int texDivY = 3;
};

#endif

