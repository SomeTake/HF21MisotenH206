//=============================================================================
//
// �r���A�[�ɃA�j���[�V���������鏈�� [ViewerAnimater.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _VIEWER_ANIMATER_H_
#define _VIEWER_ANIMATER_H_

#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ViewerAnimater
{
public:
	ViewerAnimater();
	~ViewerAnimater();

	//�A�j���[�V�����Đ�����
	static void PlayAnim(std::vector <std::function<void()>> animArray, std::function<void()> Callback = nullptr);

	//�ړ�����
	static void Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type);

	//�ړ�����
	static void Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& end, float duration, EaseType type);

	//�X�P�[������
	static void Scale(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type);

	//�t�F�[�h����
	static void Fade(BaseViewerDrawer& viewer, const float& start, const float& end, float duration, EaseType type);

	//�ҋ@����
	static void Wait(float duration);

private:

	//�t���[���J�E���g
	static int frameCnt;

	//�A�j���[�V��������
	static float animTime;

	//�A�j���[�V�����I���J�E���g
	static int finishedCnt;

	//�A�j���[�V�������I��������
	static bool isFinished;

};
#endif