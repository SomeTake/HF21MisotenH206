
//=============================================================================
//
// �A�ŃQ�[���X�^�[�^�[�r���A�[���� [BeatStarterViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_STARTER_VIEWER_H_
#define _BEAT_STARTER_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatStarterViewer :public BaseViewer
{
public:
	BeatStarterViewer();
	~BeatStarterViewer();

	void Update();
	void Draw(void);
	void SetReady(void);
	void SetGo(void);

private:
	BaseViewerDrawer *readyText;
	BaseViewerDrawer *goText;

	//���f�B�[�e�L�X�g���X�N���[���C��
	void InReady(void);

	//�S�[�e�L�X�g���o�������鏈��
	void InGo(void);

	//���f�B�[���ׂ���
	bool shouldReady;

	//�S�[���ׂ���
	bool shouldGo;

	//�t���[���J�E���g
	int countFrame;

	//�A�j���[�V��������
	float animTime;
};

#endif