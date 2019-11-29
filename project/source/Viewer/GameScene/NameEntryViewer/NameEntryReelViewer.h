
//=============================================================================
//
// ���O���̓��[������ [NameEntryReelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_REEL_VIEWER_H_
#define _NAME_ENTRY_REEL_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NameEntryReelViewer :public BaseViewer
{
public:
	NameEntryReelViewer();
	~NameEntryReelViewer();

	void Update();
	void Draw(void);

	//���[���A�b�v����
	void ReelUp(int reelCnt);

	//���[���_�E������
	void ReelDown(int reelCnt);

	//���[���̕������擾����
	int* GetReelChar(void);

private:

	//�o�^�ł��閼�O�̍ő吔
	static const int entryNameMax = 3;

	//������̍ő吔
	static const int charTypeMax = 36;

	//���[���ɕ\������Ă��镶��
	int character[entryNameMax];

	//���[��
	BaseViewerDrawer * reel[entryNameMax];
};

#endif