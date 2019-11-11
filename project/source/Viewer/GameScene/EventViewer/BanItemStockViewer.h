//=============================================================================
//
// �o���X�g�b�N�r���A�[���� [BanItemStockViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BAN_STOCK_VIEWER_H_
#define _BAN_STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BanItemStockViewer :public BaseViewer
{
public:
	BanItemStockViewer();
	~BanItemStockViewer();

	void Update(void);
	void Draw(void);

	//�p�����[�^���󂯂Ƃ锠
	bool parameterBox;

private:

	//�A�C�R��
	BaseViewerDrawer *icon;		

	//�A�j���[�V����
	void Play(void);

	//���݂̃p�����[�^
	bool currentParam;

	//�P�t���[���O�̃p�����[�^
	bool lastParam;
};


#endif