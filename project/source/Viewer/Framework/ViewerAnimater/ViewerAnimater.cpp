//=============================================================================
//
// �r���A�[�ɃA�j���[�V���������鏈�� [ViewerAnimater.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../ViewerDrawer/BaseViewerDrawer.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
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
// �U������
//=============================================================================
void ViewerAnimater::Shake(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, float duration, std::function<void()> Callback)
{
	//����U�������邩
	const int shakeNum = 400;
	//�ǂ̂��炢�̐U�ꕝ��
	const float shakeValue = 3.0f;

	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	float radian = Easing::EaseValue(animTime, 0.0f, D3DX_PI * shakeNum, OutCirc);

	viewer.position.x = start.x + shakeValue * sinf(radian);

	//�I������
	if (frameCnt < duration) return;
	viewer.position.x = start.x;
	SetAnimFinished();
}

//=============================================================================
// �z�b�s���O����
//=============================================================================
void ViewerAnimater::Hop(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, const D3DXVECTOR2 & value, float duration,std::function<void()> Callback)
{
	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	if (frameCnt <= duration/2) 
	viewer.size.y = Easing::EaseValue(animTime*2, start.y, start.y + value.y, OutCubic);
	else
	{
		viewer.size.y = Easing::EaseValue(animTime * 2, start.y + value.y, start.y, OutCubic);
	}

	//�I������
	if (frameCnt < duration) return;
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
// �ړ������i�������s�A�j���[�V��������j
//=============================================================================
void ViewerAnimater::MovePos(D3DXVECTOR2 & position, const D3DXVECTOR2 & start, const D3DXVECTOR2 & end, float duration, EaseType type, std::function<void()> Callback)
{
	//�t���[���J�E���g�Ǝ��Ԃ��X�V
	UpdateFrameAndTime(duration);

	if (Callback) Callback();

	position.x = Easing::EaseValue(animTime, start.x, end.x, type);
	position.y = Easing::EaseValue(animTime, start.y, end.y, type);

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
// �ҋ@�����i�������s�A�j���[�V��������j
//=============================================================================
void ViewerAnimater::Wait(float duration, std::function<void()> Callback)
{
	//�t���[���X�V
	frameCnt++;

	if (Callback) Callback();

	//�I������
	if (frameCnt < duration) return;
	SetAnimFinished();
}

//=============================================================================
//	�ړ������i�T�u�j
//=============================================================================
void ViewerAnimater::SubMove(BaseViewerDrawer& viewer, const D3DXVECTOR2& start,
	const D3DXVECTOR2& end, EaseType type, std::function<void()> Callback)
{
	if (Callback) Callback();

	viewer.position.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.position.y = Easing::EaseValue(animTime, start.y, end.y, type);
}

//=============================================================================
// �X�P�[�������i�T�u�j
//=============================================================================
void ViewerAnimater::SubScale(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start,
	const D3DXVECTOR2 & end, EaseType type, std::function<void()> Callback)
{
	if (Callback) Callback();

	viewer.size.x = Easing::EaseValue(animTime, start.x, end.x, type);
	viewer.size.y = Easing::EaseValue(animTime, start.y, end.y, type);
}

//=============================================================================
// �t�F�[�h�����i�T�u�j
//=============================================================================
void ViewerAnimater::SubFade(BaseViewerDrawer & viewer, const float & start, const float & end, 
	const float maltiValue, EaseType type, std::function<void()> Callback)
{
	if (Callback) Callback();

	float alpha = Easing::EaseValue(animTime*maltiValue, start, end, type);
	viewer.SetAlpha(alpha);
}

//=============================================================================
// �e�L�X�g�t�F�[�h�����i�T�u�j
//=============================================================================
void ViewerAnimater::SubFadeText(TextViewer &text, const float & start, const float & end, const float maltiValue, EaseType type, std::function<void()> Callback)
{
	if (Callback) Callback();

	float alpha = Easing::EaseValue(animTime*maltiValue, start, end, type);
	text.SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f,alpha));
}

//=============================================================================
// �z�b�s���O�����i�T�u�j
//=============================================================================
void ViewerAnimater::SubHop(BaseViewerDrawer & viewer, const D3DXVECTOR2 & start, 
	const D3DXVECTOR2 & value, float duration, std::function<void()> Callback)
{
	if (Callback) Callback();

	if (frameCnt <= duration / 2)
		viewer.size.y = Easing::EaseValue(animTime * 2, start.y, start.y + value.y, OutCubic);
	else
	{
		viewer.size.y = Easing::EaseValue(animTime * 2, start.y + value.y, start.y, OutCubic);
	}
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
// �A�j���[�V�����I�������iprivate�j
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
// �A�j���[�V�����I�������ipublic�j
//=============================================================================
void ViewerAnimater::SetPlayFinished(bool& isPlayng, std::function<void()> Callback)
{
	isPlayng = false;
	if (Callback) Callback();
}

//=============================================================================
// �A�j���[�V�������Z�b�g����
//=============================================================================
void ViewerAnimater::ResetAnim(void)
{
	frameCnt = 0;
	animTime = 0;
	finishedCnt = 0;
	isFinished = false;
}
