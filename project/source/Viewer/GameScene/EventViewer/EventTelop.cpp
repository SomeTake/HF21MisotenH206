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
	//�e�L�X�g
	text = new TelopDrawer();
	text->MakeVertexText();
	text->size = D3DXVECTOR3(512, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	text->SetColor(SET_COLOR_NOT_COLORED);

	//�w�i
	bg = new TelopDrawer();
	bg->percentage = 0.0f;
	bg->MakeVertexBG();
	bg->size = D3DXVECTOR3(SCREEN_WIDTH / 2, 60.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�R���e�i�Ƀe�N�X�`���������[�h����
	for (int i = 0; i < typeMax; i++)
	{
		LPDIRECT3DTEXTURE9 tTex;
		LPDIRECT3DTEXTURE9 bgTex;

		D3DXCreateTextureFromFile(pDevice,
			textTexPath[i],
			&tTex);

		textTexContainer.push_back(tTex);

		D3DXCreateTextureFromFile(pDevice,
			bgTexPath[i],
			&bgTex);

		bgTexContainer.push_back(bgTex);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventTelop::~EventTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// �X�V����
//=============================================================================
void EventTelop::Update()
{
	bg->PlayBG();
	Play();

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_T))
	{
		Set(PositiveEvent01, onFinish);
	}

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventTelop::Draw(void)
{
	//�w�i���ɕ`��
	if (bg->isPlaying)
	{
		bg->Draw();
		bg->SetVertexBG(bg->percentage);
	}

	if (text->isPlaying)
	{
		text->Draw();
		text->SetVertex();
	}
}

//=============================================================================
// �e���b�v�Đ�����
//=============================================================================
void EventTelop::Play()
{
	//��ʊO�֏�����
	D3DXVECTOR3 initPos = D3DXVECTOR3(3000.0f, SCREEN_HEIGHT / 2, 0.0f);
	text->position = initPos;

	if (text->isPlaying&&bg->isPlaying)
	{
		if (text->currentAnim == text->WaitBG_Open && bg->isBG_Openinig == false)
		{
			bg->PlayBG_Open();
		}
		if (text->currentAnim == text->WaitBG_Close && bg->isBG_Closing == false)
		{
			bg->PlayBG_Close();
		}

		text->countFrame++;

		text->position.x = Easing::EaseValue(text->GetCountObject(textAnimDuration[text->currentAnim]),
			textStartPositionX[text->currentAnim],
			textEndPositionX[text->currentAnim],
			textAnimType[text->currentAnim]);

		if (text->countFrame == textAnimDuration[text->currentAnim])
		{
			text->countFrame = 0;
			text->currentAnim++;
		}
		if (text->currentAnim == animMax)
		{
			text->countFrame = 0;
			text->currentAnim = 0;
			text->position = initPos;
			text->isPlaying = false;
		}
		if (text->currentAnim > animMax)
		{
			bg->isPlaying = false;

			//�Đ��I���̒ʒm
			(*onFinish)();
		}
	}
}

//=============================================================================
// �e�N�X�`�����󂯓n������
//=============================================================================
void EventTelop::PassTexture(TelopID id)
{
	text->texture = textTexContainer[id];
	bg->texture = bgTexContainer[id];
}

//=============================================================================
// �e���b�v�Z�b�g����
//=============================================================================
void EventTelop::Set(TelopID id, DelegateBase<void>* onFinish)
{
	//�e�N�X�`�����󂯓n��
	PassTexture(id);

	//�Đ���Ԃɂ���
	text->isPlaying = true;
	bg->isPlaying = true;

	//�e���b�v�Đ��I���ʒm
	this->onFinish = onFinish;
}
