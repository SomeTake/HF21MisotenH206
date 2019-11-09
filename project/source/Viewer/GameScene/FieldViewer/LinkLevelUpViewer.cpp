//=============================================================================
//
// �����N���x���A�b�v�r���A�[���� [LinkLevelUpViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "LinkLevelUpViewer.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�A�j���[�V�����̐�
static const int animMax = 5;

//�e�L�X�g�A�j���[�V�����J�n�ʒu
static const float textStartPositionY[animMax] = {
	SCREEN_HEIGHT/3*2,
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_HEIGHT/3
};

//�e�L�X�g�A�j���[�V�����I���ʒu
static const float textEndPositionY[animMax] = {
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_HEIGHT/3,
	SCREEN_HEIGHT/3
};

//�A�j���[�V�������
static const EaseType animType[animMax] = {
	OutCubic,
	OutBack,
	InOutCubic,
	InCubic,
	InOutCubic
};

//�A�j���[�V�����Ԋu(������ύX����ƃA�j���[�V�����̑����𒲐��ł���)
//*����(0������Ɩ�����ɂȂ邩��A�j���[�V�������̂��̂��폜���邱��)
static const float animDuration[animMax] = {
	15,
	20,
	40,
	15,
	10
};

//�A�j���[�V�����V�[��
enum TelopAnimScene
{
	Text_FadeIn_PopIn,
	Num_Laurel_In,
	Wait,
	Text_FadeOut_PopOut,
	Num_Laurel_Out
};

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
LinkLevelUpViewer::LinkLevelUpViewer()
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Text.png");
	text->size = D3DXVECTOR3(750.0f, 100.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, textStartPositionY[0], 0.0f);
	text->MakeVertex();
	text->SetAlpha(0.0f);

	//���j��
	laurel = new BaseViewerDrawer();
	laurel->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Laurel.png");
	laurel->size = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	laurel->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	laurel->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/2/1.5, 0.0f);
	laurel->MakeVertex();

	//�{
	plus = new BaseViewerDrawer();
	plus->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Plus.png");
	plus->size = D3DXVECTOR3(120.0f, 120.0f, 0.0f);
	plus->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	plus->position = D3DXVECTOR3(SCREEN_CENTER_X-80.0f, SCREEN_HEIGHT / 2/1.5, 0.0f);
	plus->MakeVertex();

	//����
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Number.png");
	num->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT / 2/1.5, 0.0f);
	num->intervalPosScr = 80.0f;
	num->intervalPosTex = 0.1f;
	num->placeMax = 2;
	num->baseNumber = 10;
	num->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
LinkLevelUpViewer::~LinkLevelUpViewer()
{
	SAFE_DELETE(text);
	SAFE_DELETE(laurel);
	SAFE_DELETE(plus);
	SAFE_DELETE(num);
}

//=============================================================================
// �X�V����
//=============================================================================
void LinkLevelUpViewer::Update()
{
	//�r���A�[�Đ�����
	Play();
}

//=============================================================================
// �`�揈��
//=============================================================================
void LinkLevelUpViewer::Draw(void)
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	if (currentAnim >= Num_Laurel_In)
	{
		//���j�����ɕ`��
		laurel->Draw();

		//���F
		num->DrawCounter(num->baseNumber, parameterBox,num->placeMax,
			num->intervalPosScr, num->intervalPosTex);

		//�{
		plus->Draw();
	}

	//�e�L�X�g
	text->Draw();
}

//=============================================================================
// �r���A�[�Đ�����
//=============================================================================
void LinkLevelUpViewer::Play()
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	//�t���[���X�V
	countFrame++;

	//���ԍX�V
	animTime = countFrame / animDuration[currentAnim];

	//�V�[�����Ɏ��s����T�u�A�j���[�V����
	switch (currentAnim)
	{
	case(Text_FadeIn_PopIn):
		FadeInText();
		break;
	case(Text_FadeOut_PopOut):
		FadeOutText();
		break;
	case(Num_Laurel_In):
		InNum();
		break;
	default:
		break;
	}

	//�|�W�V�������X�V
	text->position.y = Easing::EaseValue(animTime,
		textStartPositionY[currentAnim],
		textEndPositionY[currentAnim],
		animType[currentAnim]);

	//�A�j���[�V�����X�V
	if (countFrame == animDuration[currentAnim])
	{
		countFrame = 0;
		currentAnim++;
	}

	//�A�j���[�V�����I��
	if (currentAnim >= animMax)
	{
		countFrame = 0;
		currentAnim = 0;
		text->position.y = textStartPositionY[0];
		num->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		isPlaying = false;
	}
}

//=============================================================================
// �e�L�X�g�t�F�[�h�C������
//=============================================================================
void LinkLevelUpViewer::FadeInText(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float easingStart = 0.0f;
	float easingGoal = 1.0f;

	//�e�N�X�`���̃��l
	float alpha;

	alpha = Easing::EaseValue(animTime, easingStart, easingGoal, animType[Text_FadeIn_PopIn]);
	text->SetAlpha(alpha);
}

//=============================================================================
// �e�L�X�g�t�F�[�h�A�E�g����
//=============================================================================
void LinkLevelUpViewer::FadeOutText(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float easingStart = 1.0f;
	float easingGoal = 0.0f;

	//�e�N�X�`���̃��l
	float alpha;

	alpha = Easing::EaseValue(animTime, easingStart, easingGoal, animType[Text_FadeOut_PopOut]);
	text->SetAlpha(alpha);
}

//=============================================================================
// �����o������
//=============================================================================
void LinkLevelUpViewer::InNum()
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float easingStart = 0.0f;
	float easingGoal = 120.0f;

	num->size.x = Easing::EaseValue(animTime, easingStart, easingGoal, animType[Num_Laurel_In]);
	num->size.y = Easing::EaseValue(animTime, easingStart, easingGoal, animType[Num_Laurel_In]);
}

//=============================================================================
// �����N���x���A�b�v�r���A�[�Z�b�g����
//=============================================================================
void LinkLevelUpViewer::Set(int level)
{
	//�p�����[�^���󂯎��
	parameterBox = level;

	//�Đ���Ԃɂ���
	isPlaying = true;
}
