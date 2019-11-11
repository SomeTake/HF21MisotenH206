//=============================================================================
//
// �X�g�b�N����r���A�[���� [SealItemStockViewer.cpp]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../../../Framework/Math/Easing.h"
#include "SealItemStockViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// *���ӁF����A�j���[�V�����ƕ�������A�j���[�V�����͎d�l�����܂��ĂȂ����߁A
// �b��I�ɃT�C�Y�_�E���A�t�F�[�h�A�E�g�����s�B
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�A�C�R���̏����T�C�Y
D3DXVECTOR3 initIconSize(400.0f, 400.0f, 0.0f);

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
SealItemStockViewer::SealItemStockViewer()
{
	//�A�C�R��
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/EventViewer/SealItemStockViewer/SealIcon.png");
	icon->size = initIconSize;
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.5f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
SealItemStockViewer::~SealItemStockViewer()
{
	SAFE_DELETE(icon);
}

//=============================================================================
// �X�V����
//=============================================================================
void SealItemStockViewer::Update(void)
{
	//�A�j���[�V�����Đ�����
	HandlePlayAnim();

	//�A�j���[�V�����Đ�
	Play();
}

//=============================================================================
// �`�揈��
//=============================================================================
void SealItemStockViewer::Draw(void)
{
	//�v���C���Ȃ�`��
	if (!isPlaying) return;

	icon->Draw();
}

//=============================================================================
// �Đ�����
//=============================================================================
void SealItemStockViewer::Play(void)
{
	//�v���C���Ȃ���s
	if (!isPlaying) return;

	//�t���[���X�V
	countFrame++;

	//���ԍX�V
	animTime = countFrame / 30.0f;

	//���󂳂ꂽ
	if (isSealed)
	{
		//����A�j���[�V�������Đ�
		PlaySealAnim();
	}

	//���󂪉����ꂽ
	if (isUnSealed)
	{
		//��������A�j���[�V�������Đ�
		PlayUnSealAnim();
	}
}

//=============================================================================
// ����A�j���[�V�����Đ�����
//=============================================================================
void SealItemStockViewer::PlaySealAnim(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float easingStart = 400.0f;
	float easingGoal = 200.0f;

	icon->size.x = Easing::EaseValue(animTime, easingStart, easingGoal, InCubic);
	icon->size.y = Easing::EaseValue(animTime, easingStart, easingGoal, InCubic);

	if (icon->size.y == easingGoal)
	{
		isSealed = false;
	}
}

//=============================================================================
// ��������A�j���[�V�����Đ�����
//=============================================================================
void SealItemStockViewer::PlayUnSealAnim(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float easingStart = 1.0f;
	float easingGoal = 0.0f;

	//�e�N�X�`���̃��l
	float alpha;

	alpha = Easing::EaseValue(animTime, easingStart, easingGoal, OutCubic);
	icon->SetAlpha(alpha);

	if (alpha == easingGoal)
	{
		isUnSealed = false;

		//�Đ��I��
		isPlaying = false;
	}
}

//=============================================================================
// �Đ����䏈��
//=============================================================================
void SealItemStockViewer::HandlePlayAnim(void)
{
	currentParam = parameterBox;

	//�O�t���[���ł͕��󂳂�ĂȂ������̂Ɍ��݃t���[���ł͕��󂳂�Ă�
	if (currentParam == true && lastParam == false)
	{
		//����������Ȃ狭���I��
		isUnSealed = false;

		//�t���[���J�E���g���Z�b�g
		countFrame = 0;

		//�A�C�R���̃T�C�Y�ƃ��l��������
		icon->size = initIconSize;
		icon->SetAlpha(1.0f);

		//�����ԂɈڍs
		isSealed = true;

		//�Đ����Ɉڍs
		isPlaying = true;
	}

	//�O�t���[���ł͕��󂳂�Ă��̂Ɍ��݃t���[���ł͕��󂳂�ĂȂ�
	if (currentParam == false && lastParam == true)
	{
		//���󒆂Ȃ狭���I��
		isSealed = false;

		//�t���[���J�E���g�����Z�b�g
		countFrame = 0;

		//���������ԂɈڍs
		isUnSealed = true;
	}

	lastParam = parameterBox;
}
