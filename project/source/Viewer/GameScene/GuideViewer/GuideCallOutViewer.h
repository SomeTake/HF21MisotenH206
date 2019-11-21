
//=============================================================================
//
// �C�x���g���b�Z�[�W���� [GuideCallOutViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GUIDE_CALL_OUT_VIEWER_H_
#define _GUIDE_CALL_OUT_VIEWER_H_

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
class GuideCallOutViewer :public BaseViewer
{
public:
	GuideCallOutViewer();
	~GuideCallOutViewer();

	void Update(void);
	void Draw(void);

	//���b�Z�[�W�Z�b�g
	void Set(const std::string &message);

	//���b�Z�[�W�Z�b�g�J�E���^�[
	int messageSetCnt;

	//�Đ������ǂ���
	bool isPlaying;

private:

	BaseViewerDrawer * bg;
	TextViewer *text;

	//�Đ�����
	void Play();

	//�t���[���J�E���g
	int countFrame;
};

#endif