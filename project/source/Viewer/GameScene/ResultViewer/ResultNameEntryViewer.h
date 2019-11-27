
//=============================================================================
//
// ���U���g���O���͏��� [ResultNameEntryViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_NAME_ENTRY_VIEWER_H_
#define _RESULT_NAME_ENTRY_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultNameEntryViewer :public BaseViewer
{
public:
	ResultNameEntryViewer();
	~ResultNameEntryViewer();

	void Update();
	void Draw(void);

	//�o�^���擾����
	std::string GetEntryName(void);

	//�o�^��
	std::string entryName;

private:

	//�o�^�ł��閼�O�̍ő吔
	static const int entryNameMax = 3;

	//������̍ő吔
	static const int charTypeMax = 36;

	//����
	BaseViewerDrawer * character[entryNameMax];

	//�J�[�\��
	BaseViewerDrawer * cursor;

	//�e�N�X�`����UV���Z�b�g
	void SetTexture();

	//�J�[�\���̍��W���Z�b�g
	void SetCursorPos();

	//���O���͏���
	void NameInput(void);

	//�o�^���Z�b�g����
	void SetEntryName(int id);

	//����ID
	int charID[entryNameMax];

	//�����J�E���g
	int charCnt;
};

#endif