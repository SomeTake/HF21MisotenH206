//=============================================================================
//
// �A�ŃQ�[���Q�[�W�r���A�[���� [BeatGaugeViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_GAUGE_VIEWER_H_
#define _BEAT_GAUGE_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <functional>
#include <vector>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class ViewerAnimater;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatGaugeViewer :public BaseViewer
{
public:
	BeatGaugeViewer();
	~BeatGaugeViewer();

	void Update();
	void Draw(void);
	void Set(float percent);

private:
	BaseViewerDrawer *bar;
	BaseViewerDrawer *frame;
	ViewerAnimater *anim;

	//�Q�[�W�o�[�`�揈��
	void DrawBar(void);

	//�Q�[�W�p�[�Z���g
	float gaugePer;
};
#endif