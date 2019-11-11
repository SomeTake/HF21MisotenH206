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
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SealItemStockViewer :public BaseViewer
{
public:
	SealItemStockViewer();
	~SealItemStockViewer();

	void Update(void);
	void Draw(void);

	//�p�����[�^���󂯂Ƃ锠
	bool parameterBox;

private:

	//�A�C�R��
	BaseViewerDrawer *icon;		

	//�Đ�����
	void Play(void);

	//����A�j���[�V�������Đ�
	void PlaySealAnim(void);

	//��������A�j���[�V�������Đ�
	void PlayUnSealAnim(void);

	//�A�j���[�V�������䏈��
	void HandlePlayAnim(void);

	//���݂̃p�����[�^
	bool currentParam;

	//�P�t���[���O�̃p�����[�^
	bool lastParam;

	//�Đ������ǂ���
	bool isPlaying;

	//���󂳂ꂽ��
	bool isSealed;

	//���󂪉����ꂽ��
	bool isUnSealed;

	//�A�j���[�V��������
	float animTime;

	//�t���[���J�E���g
	int countFrame;
};


#endif