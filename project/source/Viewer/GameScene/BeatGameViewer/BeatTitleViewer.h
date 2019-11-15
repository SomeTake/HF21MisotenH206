
//=============================================================================
// 
// �A�ŃQ�[���^�C�g���r���A�[���� [BeatTitleViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_TITLE_VIEWER_H_
#define _BEAT_TITLE_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatTitleViewer :public BaseViewer
{
public:
	BeatTitleViewer();
	~BeatTitleViewer();

	//�^�C�g���̎��
	enum TitleID
	{
		//�{�^����A�ł��ĊX�����I
		ProtectCity,
		//�{�^����A�ł���AI����߂�I
		CalmAI,
		//��ސ�
		Max
	};

	void Update();
	void Draw(void);
	void Set(TitleID id);

private:
	BaseViewerDrawer *title;

	//�e�N�X�`�����Z�b�g
	void SetTexture(TitleID id);
};

#endif