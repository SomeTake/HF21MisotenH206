//=============================================================================
//
// �X�g�b�N����r���A�[���� [SealItemStockViewer.h]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#ifndef _SEAL_STOCK_VIEWER_H_
#define _SEAL_STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class TextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SealItemStockViewer :public BaseViewer
{
private:
	//�A�C�R��
	TextureDrawer *Icon;
	TextureDrawer *Icon_White;

	void CountDownStart(void);

public:
	SealItemStockViewer();
	~SealItemStockViewer();

	void Update(void);
	void Draw(void);
	void SetBanIcon(void);
};


#endif