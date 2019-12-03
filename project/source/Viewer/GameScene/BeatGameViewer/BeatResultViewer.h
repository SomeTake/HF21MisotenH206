
//=============================================================================
//
// �A�ŃQ�[�����ʃr���A�[���� [BeatResultViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_RESULT_VIEWER_H_
#define _BEAT_RESULT_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class ViewerAnimater;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatResultViewer :public BaseViewer
{
public:
	BeatResultViewer();
	~BeatResultViewer();

	//���ʂ̎��
	enum ResultID
	{
		Success,
		Failed,
		Max
	};

	void Update();
	void Draw(void);
	void Set(ResultID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer * text;
	BaseViewerDrawer *bg;
	ViewerAnimater *anim;

	//�Đ��I���ʒm
	std::function<void(void)> Callback;

	//�e�N�X�`�����󂯓n��
	void SetTexture(ResultID id);
};

#endif