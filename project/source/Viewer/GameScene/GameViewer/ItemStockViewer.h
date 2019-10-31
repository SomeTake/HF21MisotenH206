//=============================================================================
//
// �X�g�b�N�r���A�[���� [ItemStockViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STOCK_VIEWER_H_
#define _STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ItemStockViewer :public BaseViewer
{
public:
	ItemStockViewer();
	~ItemStockViewer();

	void Update(void);
	void Draw(void);

	//�p�����[�^���󂯂Ƃ锠
	int parameterBox;
	bool InBanStock;
	bool BanIconDebut;
	bool InPauseEvent;

private:
	BaseViewerDrawer *icon;				// �X�g�b�N�A�C�R��
	BaseViewerDrawer *BanIcon;			// �o�c�A�C�R��
	BaseViewerDrawer *BanIcon_White;	// �o�c�A�C�R��(��)
	CountViewerDrawer *num;

	//�A�j���[�V����
	void Animate(void);
	void SetBanIconVertex(float Percent);
	void SetBanIconTexture(float Percent);
};


#endif