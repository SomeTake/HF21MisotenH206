//=============================================================================
//
// �C�x���g�e���b�v���� [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/TelopDrawer.h"
#include "../../../../Framework/Input/input.h"
#include"../../../../Framework/Math/Easing.h"
#include "EventTelop.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�e���b�v�̎�ސ�
const int EventTelop::typeMax;

//�e�L�X�g�̃e�N�X�`���p�X
static const char *textTexPath[EventTelop::typeMax]
{
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/PositiveText01.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/PositiveText02.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/NegativeText01.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/NegativeText02.png",
};

//�w�i�̃e�N�X�`���p�X
static const char *bgTexPath[EventTelop::typeMax]
{
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/PositiveBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/PositiveBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/NegativeBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/NegativeBG.png",
};

//�A�j���[�V�����̐�
static const int animMax = 5;

//�e�L�X�g�A�j���[�V�����J�n�ʒu
static const float textStartPositionX[animMax] = {
	SCREEN_WIDTH*1.5,
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5
};

//�e�L�X�g�A�j���[�V�����I���ʒu
static const float textEndPositionX[animMax] = {
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5,
	-SCREEN_WIDTH * 1.5
};

//�e�L�X�g�A�j���[�V�������
static const EaseType textAnimType[animMax] = {
	InOutCubic,
	InOutCubic,
	InOutCubic,
	InOutCubic,
	InOutCubic
};

//�e�L�X�g�A�j���[�V�����Ԋu
static const float textAnimDuration[animMax] = {
	10,
	120,
	100,
	120,
	10
};

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventTelop::EventTelop()
{
	for (int i = 0; i < typeMax; i++)
	{
		//�e�L�X�g
		text[i] = new TelopDrawer();
		text[i]->isActive = false;
		text[i]->LoadTexture(textTexPath[i]);
		text[i]->MakeVertexText();
		text[i]->size = D3DXVECTOR3(512, 128.0f, 0.0f);
		text[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		text[i]->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
		text[i]->SetColor(SET_COLOR_NOT_COLORED);

		//�w�i
		bg[i] = new TelopDrawer();
		bg[i]->isActive = false;
		bg[i]->percentage = 0.0f;
		bg[i]->LoadTexture(bgTexPath[i]);
		bg[i]->MakeVertexBG();
		bg[i]->size = D3DXVECTOR3(SCREEN_WIDTH / 2, 60.0f, 0.0f);
		bg[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg[i]->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
		bg[i]->SetColor(SET_COLOR_NOT_COLORED);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventTelop::~EventTelop()
{
	for (int i = 0; i < typeMax; i++)
	{
		SAFE_DELETE(text[i]);
		SAFE_DELETE(bg[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void EventTelop::Update(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		bg[i]->PlayBG();
		Play(i);
	}

	text[PositiveEvent01]->isActive = true;
	bg[PositiveEvent01]->isActive = true;

	if (Keyboard::GetTrigger(DIK_T))
	{
		text[PositiveEvent01]->isPlaying = true;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventTelop::Draw(void)
{
	for (int i = 0; i < typeMax; i++)
	{
		//�w�i���ɕ`��
		if (bg[i]->isActive)
		{
			bg[i]->Draw();
			bg[i]->SetVertexBG(bg[i]->percentage);
		}

		if (text[i]->isActive)
		{
			text[i]->Draw();
			text[i]->SetVertex();
		}
	}
}

//=============================================================================
// �e���b�v�Đ�����
//=============================================================================
void EventTelop::Play(int i)
{
	//��ʊO�֏�����
	D3DXVECTOR3 initPos = D3DXVECTOR3(3000.0f, SCREEN_HEIGHT / 2, 0.0f);
	text[i]->position = initPos;

	if (text[i]->isPlaying)
	{
		if (text[i]->currentAnim == text[i]->WaitBG_Open && bg[i]->isBG_Openinig == false)
		{
			bg[i]->PlayBG_Open();
		}
		if (text[i]->currentAnim == text[i]->WaitBG_Close && bg[i]->isBG_Closing == false)
		{
			bg[i]->PlayBG_Close();
		}

		text[i]->countFrame++;

		text[i]->position.x = Easing::EaseValue(text[i]->GetCountObject(textAnimDuration[text[i]->currentAnim]),
			textStartPositionX[text[i]->currentAnim],
			textEndPositionX[text[i]->currentAnim],
			textAnimType[text[i]->currentAnim]);

		if (text[i]->countFrame == textAnimDuration[text[i]->currentAnim])
		{
			text[i]->countFrame = 0;
			text[i]->currentAnim++;
		}
		if (text[i]->currentAnim == animMax)
		{
			text[i]->countFrame = 0;
			text[i]->currentAnim = 0;
			text[i]->position = initPos;
			text[i]->isPlaying = false;
		}
	}
}

//=============================================================================
// �e���b�v�Z�b�g����
//=============================================================================
void EventTelop::Set(TelopID id, DelegateBase<void>* onFinish)
{
	//�A�N�e�B�u�ɂ���
	text[id]->isActive = true;
	bg[id]->isActive = true;

	//�e���b�v�Đ��I���ʒm
	onFinish;
}
