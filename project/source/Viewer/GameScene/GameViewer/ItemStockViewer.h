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

	//�X�g�b�N�r���A�[�̎��
	enum ItemStockViewerType
	{
		Bridge,
		Drill,
		Insurance,
		EDF
	};

	//�X�g�b�N�r���A�[�̎�ސ�
	static const int typeMax = 4;

	//�p�����[�^���󂯂Ƃ锠
	int parameterBox[typeMax];

private:
	BaseViewerDrawer *icon[typeMax];
	CountViewerDrawer *num[typeMax];

	//���݂̃p�����[�^
	int currentParam[typeMax] = {};

	//�P�t���[���O�̃p�����[�^
	int lastParam[typeMax] = {};

	//�A�j���[�V����
	void Animate(void);
};


#endif