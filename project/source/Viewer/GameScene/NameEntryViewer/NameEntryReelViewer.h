//=============================================================================
//
// ���O���̓��[������ [NameEntryReelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_REEL_VIEWER_H_
#define _NAME_ENTRY_REEL_VIEWER_H_

#include <functional>
#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;
class ViewerAnimater;

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

	bool MoveCursorRight(void);
	bool MoveCursorLeft(void);

	void SetTelopIn();
	void SetTelopOut();

	// �J�[�\���������邩�ǂ����̃t���O���擾
	bool GetCursorMovable(void) { return this->CursorMovable; };

private:

	enum AnimScene
	{
		TelopIn,
		TelopOut,
		Max
	};

	//�o�^�ł��閼�O�̍ő吔
	static const int entryNameMax = 3;

	//������̍ő吔
	static const int charTypeMax = 36;

	//���[���ɕ\������Ă��镶��
	int character[entryNameMax];

	bool isInPlaying;
	bool isOutPlaying;

	// �J�[�\�����ړ��ł��邩�ǂ���
	bool CursorMovable;

	BaseViewerDrawer * reel[entryNameMax];
	BaseViewerDrawer * cursor;
	BaseViewerDrawer * bg;
	TextViewer *text;
	TextViewer *underBar;
	ViewerAnimater *anim[AnimScene::Max];

	void InReel(std::function<void()> Callback);
	void OutReel(std::function<void()> Callback);
};

#endif