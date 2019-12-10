//=============================================================================
//
// ���O�o�^�r���A�[�R���g���[������ [NameEntryViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_VIEWER_H_
#define _NAME_ENTRY_VIEWER_H_

#include <vector>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class NameEntryInput;
class NameEntryReelViewer;
class NameEntryBgViewer;
class NameEntryInfoViewer;
class NameEntryCursorViewer;
class BaseViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NameEntryViewer
{
public:
	NameEntryViewer();
	~NameEntryViewer();

	void Update(void);
	void Draw(void);

	//�A�N�e�B�u��Ԃ��Z�b�g
	void SetActive(bool flag);

	bool GetIsActive();

	//�o�^��ID�擾�����i�����e�[�u����0�`35�܂ł̒l��entryNameMax�̔z��j
	int* GetEntryNameID();

	void SlideNameEntryViewer(bool isIn);
private:
	std::vector <BaseViewer*> nameEntryViewer;
	NameEntryInput *input;
	NameEntryReelViewer *reelViewer;
	NameEntryBgViewer *bgViewer;

	//�J�[�\���ړ�����
	void MoveCursor(void);

	//���[���㉺����
	void UpDownReel(void);

	//�o�^���Z�b�g����
	void SetEntryName();

	//�o�^�ł��閼�O�̍ő吔
	static const int entryNameMax = 3;

	//�o�^���̕����e�[�u��ID
	int entryNameID[entryNameMax];

	//���[���J�E���g
	int reelCnt;

	//�A�N�e�B�u���ǂ���
	bool isActive;
};

#endif

