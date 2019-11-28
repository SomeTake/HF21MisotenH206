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

	std::string GetEntryName();

private:
	std::vector <BaseViewer*> nameEntryViewer;
	NameEntryInput *input;
	NameEntryReelViewer *reelViewer;
	NameEntryCursorViewer *cursorViewer;

	//�o�^��
	std::string entryName;

	//�J�[�\���ړ�����
	void MoveCursor(void);

	//���[���㉺����
	void UpDownReel(void);

	//�o�^���Z�b�g����
	void SetEntryName();

	//�o�^�ł��閼�O�̍ő吔
	static const int entryNameMax = 3;

	//���[���J�E���g
	int reelCnt;

	//�A�N�e�B�u���ǂ���
	bool isActive;
};

#endif

