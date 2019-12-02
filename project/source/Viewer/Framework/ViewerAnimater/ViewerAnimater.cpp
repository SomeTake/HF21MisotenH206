//=============================================================================
//
// �r���A�[�ɃA�j���[�V���������鏈�� [ViewerAnimater.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../ViewerDrawer/BaseViewerDrawer.h"
#include "ViewerAnimater.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ViewerAnimater::ViewerAnimater():
	frameCnt(0),
	animTime(0),
	finishedCnt(0),
	isFinished(false)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ViewerAnimater::~ViewerAnimater()
{
	this->animArray.clear();
}

//=============================================================================
// �A�j���[�V�����Đ�����
//=============================================================================
void ViewerAnimater::PlayAnim(std::function<void()> Callback)
{
	//���I����ԂɈڍs
	isFinished = false;

	//�z��̒��̃A�j���[�V���������s
	this->animArray[finishedCnt]();

	//�I��������I���J�E���g���J�E���g�A�b�v
	if (isFinished)
		finishedCnt++;

	//�I�������񐔂��A�j���[�V�������ɒB������
	if (finishedCnt == this->animArray.size())
	{
		finishedCnt = 0;
		SetAnimFinished();

		//�I���ʒm
		if (Callback) Callback();
	}
}

//=============================================================================
// �ړ�����
//=============================================================================
void ViewerAnimater::Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start,
	const D3DXVECTOR2& end, float duration, EaseType type)
{
	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	viewer.position.x =  Easing::EaseValue(animTime,start.x,end.x,type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//�I������
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// �X�P�[������
//=============================================================================
void ViewerAnimater::Scale(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, 
	const D3DXVECTOR2 & end, float duration, EaseType type)
{
	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	viewer.size.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.size.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//�I������
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// �t�F�[�h����
//=============================================================================
void ViewerAnimater::Fade(BaseViewerDrawer & viewer, const float & start, 
	const float & end, float duration, EaseType type)
{
	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	float alpha = Easing::EaseValue(animTime, start, end, type);
	viewer.SetAlpha(alpha);

	//�I������
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// �U������
//=============================================================================
void ViewerAnimater::Shake(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, float duration)
{
	//����U�������邩
	const int shakeNum = 400;
	//�ǂ̂��炢�̐U�ꕝ��
	const float shakeValue = 10.0f;

	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	float radian = Easing::EaseValue(animTime, 0.0f, D3DX_PI * shakeNum, OutCirc);

	viewer.position.x = start.x + shakeValue * sinf(radian);
	viewer.position.y = start.y + shakeValue * sinf(radian);

	//�I������
	if (frameCnt < duration) return;
	viewer.position.x = start.x;
	viewer.position.y = start.y;
	SetAnimFinished();
}

//=============================================================================
// �ړ������i�������s�A�j���[�V��������j
//=============================================================================
void ViewerAnimater::Move(BaseViewerDrawer& viewer, const D3DXVECTOR2& start,
	const D3DXVECTOR2& end, float duration, EaseType type, std::function<void()> Callback)
{
	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	viewer.position.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//�I������
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// �X�P�[�������i�������s�A�j���[�V��������j
//=============================================================================
void ViewerAnimater::Scale(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start,
	const D3DXVECTOR2 & end, float duration, EaseType type, std::function<void()> Callback)
{
	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	viewer.size.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.size.y = Easing::EaseValue(animTime, start.y, end.y, type);

	//�I������
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// �t�F�[�h�����i�������s�A�j���[�V��������j
//=============================================================================
void ViewerAnimater::Fade(BaseViewerDrawer & viewer, const float & start,
	const float & end, float duration, EaseType type, std::function<void()> Callback)
{
	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	float alpha = Easing::EaseValue(animTime, start, end, type);
	viewer.SetAlpha(alpha);

	//�I������
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
//	�ړ������i�T�u�j
//=============================================================================
void ViewerAnimater::SubMove(BaseViewerDrawer& viewer, const D3DXVECTOR2& start,
	const D3DXVECTOR2& end, EaseType type)
{
	viewer.position.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);
}

//=============================================================================
// �X�P�[�������i�T�u�j
//=============================================================================
void ViewerAnimater::SubScale(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start,
	const D3DXVECTOR2 & end, EaseType type)
{
	viewer.size.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.size.y = Easing::EaseValue(animTime, start.y, end.y, type);
}

//=============================================================================
// �t�F�[�h�����i�T�u�j
//=============================================================================
void ViewerAnimater::SubFade(BaseViewerDrawer & viewer, const float & start,
	const float & end, EaseType type)
{
	float alpha = Easing::EaseValue(animTime*1.5f, start, end, type);
	viewer.SetAlpha(alpha);
}

//=============================================================================
// �ҋ@����
//=============================================================================
void ViewerAnimater::Wait(float duration)
{
	//�t���[���X�V
	frameCnt++;

	//�I������
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
// �t���[���J�E���g�Ǝ��Ԃ̍X�V����
//=============================================================================
void ViewerAnimater::UpdateFrameAndTime(float duration)
{
	//�t���[���X�V
	frameCnt++;

	//���ԍX�V
	animTime = frameCnt / duration;
}

//=============================================================================
// �A�j���[�V�����I������
//=============================================================================
void ViewerAnimater::SetAnimFinished(void)
{
	frameCnt = 0;
	animTime = 0;

	//�I����ԂɈڍs
	isFinished = true;
}

//=============================================================================
// �A�j���[�V��������ݒ菈��
//=============================================================================
void ViewerAnimater::SetAnimBehavior(std::vector<std::function<void()>> animArray)
{
	for (unsigned int i = 0; i < animArray.size(); i++)
	{
		this->animArray.push_back(animArray[i]);
	}
}

//=============================================================================
// �A�j���[�V�����I������
//=============================================================================
void ViewerAnimater::SetPlayFinished(bool& isPlayng, std::function<void()> Callback)
{
	isPlayng = false;
	if (Callback) Callback();
}
