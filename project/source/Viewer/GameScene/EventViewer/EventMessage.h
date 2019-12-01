
//=============================================================================
//
// �C�x���g���b�Z�[�W���� [EventMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_MESSAGE_H_
#define _EVENT_MESSAGE_H_

#include "../../Framework/BaseViewer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include <functional>
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
	ViewerAnimater *anim;

	//�Đ�����
	void Play(void);

	//�A�j���[�V�����̓����ݒ�
	void SetAnimBehavior(void);

	//�A�j���[�V�����I��
	bool SetPlayFinished(void);

	//�A�j���[�V�����z��
	std::vector <std::function<void()>> animArray;

};

#endif