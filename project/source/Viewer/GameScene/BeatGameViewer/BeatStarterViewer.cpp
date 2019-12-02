//=============================================================================
//
// �A�ŃQ�[���X�^�[�^�[�r���A�[���� [BeatStarterViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "BeatStarterViewer.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//���f�B�[�e�L�X�g�ҋ@�|�W�V����X
static const float readyTextWaitPosX = SCREEN_WIDTH * 1.5;

//�S�[�e�L�X�g�ҋ@�T�C�YY
static const float goTextWaitSizeY = 0.0f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BeatStarterViewer::BeatStarterViewer()
{
	//���f�B�[�e�L�X�g
	readyText = new BaseViewerDrawer();
	readyText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatStarterViewer/Text.png");
	readyText->size = D3DXVECTOR3(600.0f, 300.0f, 0.0f);
	readyText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	readyText->position = D3DXVECTOR3(readyTextWaitPosX, SCREEN_CENTER_Y, 0.0f);
	readyText->MakeVertex();
	readyText->SetTexture(1, 2, 0);

	//�S�[�e�L�X�g
	goText = new BaseViewerDrawer();
	goText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatStarterViewer/Text.png");
	goText->size = D3DXVECTOR3(600.0f, 0.0f, 0.0f);
	goText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	goText->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	goText->MakeVertex();
	goText->SetTexture(1, 2, 1);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BeatStarterViewer::~BeatStarterViewer()
{
	SAFE_DELETE(readyText);
	SAFE_DELETE(goText);
}

//=============================================================================
// �X�V����
//=============================================================================
void BeatStarterViewer::Update()
{
	if (shouldReady)
		//���f�B�[�e�L�X�g
		InReady();

	if (shouldGo)
		//�S�[�e�L�X�g
		InGo();
}

//=============================================================================
// �`�揈��
//=============================================================================
void BeatStarterViewer::Draw(void)
{
	if(shouldReady)
		//���f�B�[�e�L�X�g
		readyText->Draw();

	if(shouldGo)
		//�S�[�e�L�X�g
		goText->Draw();
}

//=============================================================================
// ���f�B�[�e�L�X�g���X�N���[���C�����鏈��
//=============================================================================
void BeatStarterViewer::InReady(void)
{
	//�t���[���X�V
	countFrame++;

	//���ԍX�V
	animTime = countFrame / 15.0f;

	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float readyTextEasingStart = readyTextWaitPosX;
	float readyTextEasingGoal = SCREEN_CENTER_X;

	//���f�B�[�e�L�X�g�̍��W���X�V
	readyText->position.x = Easing::EaseValue(animTime, readyTextEasingStart, readyTextEasingGoal, OutCirc);
}

//=============================================================================
// �S�[�e�L�X�g���o�������鏈��
//=============================================================================
void BeatStarterViewer::InGo(void)
{
	//�t���[���X�V
	countFrame++;

	//���ԍX�V
	animTime = countFrame / 10.0f;

	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float goTextEasingStart = goTextWaitSizeY;
	float goTextEasingGoal = 300.0f;

	//�S�[�e�L�X�g�̃T�C�Y���X�V
	goText->size.y = Easing::EaseValue(animTime, goTextEasingStart, goTextEasingGoal, OutExpo);

	//��莞�Ԍo�߂ŏ���
	if (countFrame == 50.0f)
	{
		shouldGo = false;
	}
}

//=============================================================================
// ���f�B�[�e�L�X�g�Z�b�g����
//=============================================================================
void BeatStarterViewer::SetReady(void)
{
	//�S�[�e�L�X�g�������I��
	shouldGo = false;

	//�t���[��������
	countFrame = 0;

	//�A�j���[�V�������ԏ�����
	animTime = 0;

	//�|�W�V������ҋ@�ʒu�ɃZ�b�g
	readyText->position.x = readyTextWaitPosX;

	//�Đ���Ԃɂ���
	shouldReady = true;
}

//=============================================================================
// �S�[�e�L�X�g�Z�b�g����
//=============================================================================
void BeatStarterViewer::SetGo(void)
{
	//���f�B�[�e�L�X�g�������I��
	shouldReady = false;

	//�t���[��������
	countFrame = 0;

	//�A�j���[�V�������ԏ�����
	animTime = 0;

	//�T�C�Y��ҋ@�T�C�Y�ɃZ�b�g
	goText->size.y = goTextWaitSizeY;

	//�Đ���Ԃɂ���
	shouldGo = true;
}
