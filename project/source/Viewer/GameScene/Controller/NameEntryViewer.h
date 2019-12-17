//=============================================================================
//
// ���O�o�^�r���A�[�R���g���[������ [NameEntryViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_VIEWER_H_
#define _NAME_ENTRY_VIEWER_H_

#include <vector>
#include <string>

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

	void Init(void);
	void Update(void);
	void Draw(void);

	//�A�N�e�B�u��Ԃ��Z�b�g
	void SetActive(bool flag);
	bool GetIsActive(void);

	//�o�^��ID�擾�����i�����e�[�u����0�`35�܂ł̒l��entryNameMax�̔z��j
	std::string GetEntryNameID();

	void SlideNameEntryViewer(bool isIn);

	// �v���C���[�l�[�������͂��ꂽ�t���O�𐧌䂷��i���C�j
	bool GetNameEntered(void) { return this->NameEntered; };
	void SetNameEntered(bool Flag) { this->NameEntered = Flag; };

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

	// int�^�̃l�[����string�^�ɕϊ�
	std::string IntToString(int NameInt);

	//�o�^�ł��閼�O�̍ő吔
	static const int entryNameMax = 3;

	//�o�^���̕����e�[�u��ID
	int entryNameID[entryNameMax];

	//���[���J�E���g
	int reelCnt;

	//�A�N�e�B�u���ǂ���
	bool isActive;

	// �v���C���[�l�[�������͂��ꂽ���ǂ���
	bool NameEntered;
};

#endif

