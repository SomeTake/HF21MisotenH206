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
class ViewerAnimater;

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

	//���b�Z�[�W�Z�b�g����
	void SetEventMessage(const std::string &message, int &cnt);

	//�Đ���Ԏ擾����
	bool GetIsPlaying(void);

private:
	BaseViewerDrawer *bg;
	TextViewer *text;
	ViewerAnimater *anim;

	//���b�Z�[�W�Z�b�g�J�E���^�[
	int messageSetCnt;
};

#endif