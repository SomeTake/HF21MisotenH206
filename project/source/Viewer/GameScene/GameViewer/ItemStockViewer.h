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

private:
	BaseViewerDrawer *icon;
	CountViewerDrawer *num;

	//�A�j���[�V����
	void Hop(void);

	//���݂̃p�����[�^
	int currentParam;

	//�P�t���[���O�̃p�����[�^
	int lastParam;
};


#endif