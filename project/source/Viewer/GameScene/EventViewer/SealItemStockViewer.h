//=============================================================================
//
// �X�g�b�N����r���A�[���� [SealItemStockViewer.h]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#ifndef _SEAL_STOCK_VIEWER_H_
#define _SEAL_STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

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
	std::function<bool(void)> GetInPause;

	void CountDownStart(void);

public:
	SealItemStockViewer();
	~SealItemStockViewer();

	void Update(void);
	void Draw(void);
	void SetBanIcon(std::function<bool(void)> func);
	void Reset(void);
};


#endif