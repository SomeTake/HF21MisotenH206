
//=============================================================================
//
// ���O���̓C���v�b�g���� [NameEntryInput.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_INPUT_H_
#define _NAME_ENTRY_INPUT_H_

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class NameEntryInput
{
public:
	NameEntryInput();
	~NameEntryInput();

	//���[���A�b�v���͎擾����
	bool GetReelUp(void);
	//���[���_�E�����͎擾����
	bool GetReelDown(void);
	//�J�[�\�����ړ����͎擾����
	bool GetCursorRight(void);
	//�J�[�\���E�ړ����͎擾����
	bool GetCursorLeft(void);
	//�G���g���[�I�����͎擾����
	bool GetFinishedEntry(void);
};

#endif