
//=============================================================================
//
// �A�ŃQ�[���Q�[�W�r���A�[���� [BeatGaugeViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_GAUGE_VIEWER_H_
#define _BEAT_GAUGE_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

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

	//�Q�[�W�o�[�`�揈��
	void DrawBar(void);

	//�k�킹��
	void Shake(void);

	//�U�����䏈��
	void HandleShake(void);

	//�k�킹��ׂ���
	bool shouldShake;

	//�t���[���J�E���g
	int countFrame;

	//�A�j���[�V��������
	float animTime;

	//�Q�[�W�p�[�Z���g
	float gaugePer;

	//���݃t���[���̃p�����[�^
	float currentParam;

	//�O�t���[���̃p�����[�^
	float lastParam;

	//�U���p�̃��W�A��
	float radian;
};

#endif