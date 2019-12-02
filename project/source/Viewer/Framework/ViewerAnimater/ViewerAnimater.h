//=============================================================================
//
// �r���A�[�ɃA�j���[�V���������鏈�� [ViewerAnimater.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _VIEWER_ANIMATER_H_
#define _VIEWER_ANIMATER_H_

#include "../../../../main.h"
#include <functional>
#include "../../../../Framework/Math/Easing.h"

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
	void PlayAnim(std::function<void()> Callback = nullptr);

	//�ړ�����
	void Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type);
	//�X�P�[������
	void Scale(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type);
	//�t�F�[�h����
	void Fade(BaseViewerDrawer& viewer, const float& start, const float& end, float duration, EaseType type);
	//�U������
	void Shake(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, float duration);
	//�ҋ@����
	void Wait(float duration);

	//*****************************************************************************
	// �ȉ��ACallback�œ����Ɏ��s���鏈�����Ăׂ�ver.
	// ex)�t�F�[�h�A�E�g���Ȃ���X�N���[���A�E�g...etc
	// ���ӁFCallback�ŃA�j���[�V�������Ăԏꍇ�ASub���g������
	//*****************************************************************************

	//�ړ�����
	void Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type, std::function<void()> Callback);
	//�X�P�[������
	void Scale(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, float duration, EaseType type, std::function<void()> Callback);
	//�t�F�[�h����
	void Fade(BaseViewerDrawer& viewer, const float& start, const float& end, float duration, EaseType type, std::function<void()> Callback);
	//�ҋ@����
	void Wait(float duration, std::function<void()> Callback);

	//�ړ�����
	void SubMove(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, EaseType type);
	//�X�P�[������
	void SubScale(BaseViewerDrawer& viewer, const D3DXVECTOR2& start, const D3DXVECTOR2& end, EaseType type);
	//�t�F�[�h����
	void SubFade(BaseViewerDrawer& viewer, const float& start, const float& end, const float maltiValue,EaseType type);

	//�A�j���[�V�����̓����ݒ�
	void SetAnimBehavior(std::vector <std::function<void()>> animArray);

	//�A�j���[�V�����I������
	void SetPlayFinished(bool& isPlayng, std::function<void()> Callback = nullptr);

	//�A�j���[�V�����̃��Z�b�g����
	void ResetAnim(void);

private:

	//�A�j���[�V�����I������
	void SetAnimFinished(void);

	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	void UpdateFrameAndTime(float duration);

	//�t���[���J�E���g
	int frameCnt;

	//�A�j���[�V��������
	float animTime;

	//�A�j���[�V�����I���J�E���g
	int finishedCnt;

	//�A�j���[�V�������I��������
	bool isFinished;

	//�A�j���[�V�����z��
	std::vector <std::function<void()>> animArray;
};
#endif