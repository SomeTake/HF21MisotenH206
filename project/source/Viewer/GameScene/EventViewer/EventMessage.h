
//=============================================================================
//
// �C�x���g���b�Z�[�W���� [EventMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_MESSAGE_H_
#define _EVENT_MESSAGE_H_

#include "../../Framework/BaseViewer.h"
#include <string>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventMessage :public BaseViewer
{
public:
	EventMessage();
	~EventMessage();

	void Update(void);
	void Draw(void);

	//���b�Z�[�W�Z�b�g
	void SetEventMessage(const std::string &message, int &cnt);

	//���b�Z�[�W�Z�b�g�J�E���^�[
	int messageSetCnt;

	//�Đ������ǂ���
	bool isPlaying;

private:
	BaseViewerDrawer *bg;
	TextViewer *text;

	//�A�j���[�V��������
	float animTime;

	//�t���[���J�E���g
	int countFrame;

	//���ݍĐ����̃A�j���[�V����
	int currentAnim;

	//���l
	float alpha = 1.0f;

	//�Đ�����
	void Play(void);

	//�t�F�[�h�A�E�g����
	void FadeOut(void);
};

#endif