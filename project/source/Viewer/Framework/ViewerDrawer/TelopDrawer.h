//=============================================================================
//
// �e���b�v�`��p���� [TelopDrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TELOP_DRAWER_H_
#define _TELOP_DRAWER_H_

#include "BaseViewerDrawer.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TelopDrawer :public BaseViewerDrawer
{
public:
	TelopDrawer();
	~TelopDrawer();

	void MakeVertexBG();
	void MakeVertexText();

	void SetVertex();
	void SetVertexBG(float percentage);

	float percentage;

	void PlayBG_Open();
	void PlayBG_Close();

	void PlayBG(void);

	float GetCountObject(float duration);

	bool isPlaying;

	bool isBG_Openinig;
	bool isBG_Closing;

	int countFrame;
	int currentAnim;

private:
	void OpenBG(void);
	void CloseBG(void);

	float bgEasingStart;
	float bgEasingGoal;

};

#endif

