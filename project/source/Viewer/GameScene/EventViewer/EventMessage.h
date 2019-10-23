
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

	void SetEventMessage(const std::string &message);

private:
	BaseViewerDrawer *bg;
	TextViewer *text;

	//�t���[���J�E���g
	int countFrame;

	//���ݍĐ����̃A�j���[�V����
	int currentAnim;

	//�Đ������ǂ���
	bool isPlaying;

	//���l
	float alpha = 1.0f;

	//�A�j���[�V����������
	void Animate(void);

	//�t�F�[�h�A�E�g������
	void FadeOut(void);
};

#endif