//=============================================================================
//
// �C�x���g���b�Z�[�W���� [EventMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "EventMessage.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�A�j���[�V�����̐�
static const int animMax = 3;

static const float intervalViewerPos = 100.0f;

//�A�j���[�V�����J�n�ʒu
static const D3DXVECTOR2 animStartPosition[animMax] = {
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT*1.5)),
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT/10*5.5)),
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT / 10 * 5.5)),
};

//�A�j���[�V�����I���ʒu
static const D3DXVECTOR2 animEndPosition[animMax] = {
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT / 10 * 5.5)),
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT / 10 * 5.5)),
	D3DXVECTOR2((float)(SCREEN_WIDTH*1.2),(float)(SCREEN_HEIGHT / 10 * 5.5)),
};

//�A�j���[�V�������
static const EaseType animType[animMax] = {
	InOutCubic,
	InOutCubic,
	InOutCubic,
};

//�A�j���[�V�����Ԋu
static const float animDuration[animMax] = {
	50,
	50,
	30,
};

//�A�j���[�V�����V�[��
enum animScene
{
    In,
	Wait,
	Out
};

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventMessage::EventMessage()
{
	//�e�L�X�g
	text = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf",40);
	text->SetColor(SET_COLOR_NOT_COLORED);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 8.6), (int)(SCREEN_HEIGHT*1.5));

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventMessage/BG.png");
	bg->MakeVertex();
	bg->size = D3DXVECTOR3(280.0f, 52.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 8.6), (float)(SCREEN_HEIGHT*1.5),0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventMessage::~EventMessage()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// �X�V����
//=============================================================================
void EventMessage::Update(void)
{
	if (isPlaying)
	{
		Animate();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventMessage::Draw(void)
{
	//�w�i���ɕ`��
	bg->Draw();
	bg->SetVertex();

	text->Draw();
}

//=============================================================================
// �A�j���[�V��������
//=============================================================================
void EventMessage::Animate(void)
{
	//�Đ����Ȃ���s
	if (isPlaying)
	{
		//�t���[���X�V
		countFrame++;

		//�|�W�V����
		D3DXVECTOR2 position;

		//�|�W�V�������J�n�ʒu�ɏ�����
		position = animStartPosition[0];
		
		//���ԍX�V
		time = countFrame / animDuration[currentAnim];

		//�|�W�V�������X�V
		position = Easing::EaseValue((time),
		animStartPosition[currentAnim],
		animEndPosition[currentAnim],
		animType[currentAnim]);

		//�A�j���[�V�����X�V
		if (countFrame == animDuration[currentAnim])
		{
			countFrame = 0;
			currentAnim++;
		}

		//Out�V�[�����̓t�F�[�h�A�E�g�����s
		if (currentAnim == Out)
		{
			FadeOut();
		}

		//�A�j���[�V�����I��
		if (currentAnim == animMax)
		{
			countFrame = 0;
			currentAnim = 0;
			time = 0;
			alpha = 1.0f;
			text->SetColor(SET_COLOR_NOT_COLORED);
			bg->SetColor(SET_COLOR_NOT_COLORED);
			isPlaying = false;
		}

		//�|�W�V�������Z�b�g(*��ɕύX�\��)
		text->SetPos((int)position.x,(int)position.y + int((messageSetCnt-1) * intervalViewerPos));
		bg->position = D3DXVECTOR3(position.x, position.y + (messageSetCnt-1) * intervalViewerPos, 0.0f);
	}
}

//=============================================================================
// �t�F�[�h�A�E�g����
//=============================================================================
void EventMessage::FadeOut(void)
{
	//�t�F�[�h�A�E�g���̓��l�����Z
	if (alpha > 0.0f)
	{
		alpha -= 0.05f;
	}
	if (alpha < 0.0f)
	{
		alpha = 0.0f;
	}

	text->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	bg->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
}

//=============================================================================
// ���b�Z�[�W���Z�b�g����
//=============================================================================
void EventMessage::Reset(void)
{
	//�Đ���Ԃ����Z�b�g
	isPlaying = false;

	//�|�W�V����
	D3DXVECTOR2 position;

	//�|�W�V�������J�n�ʒu�ɏ�����
	position = animStartPosition[0];

	//�|�W�V�������Z�b�g(*��ɕύX�\��)
	text->SetPos((int)position.x, (int)position.y);
	bg->position = D3DXVECTOR3(position.x, position.y, 0.0f);

	countFrame = 0;
	currentAnim = 0;
	time = 0;
	alpha = 1.0f;
	text->SetColor(SET_COLOR_NOT_COLORED);
	bg->SetColor(SET_COLOR_NOT_COLORED);
	isPlaying = false;
}

//=============================================================================
// ���b�Z�[�W�Z�b�g����
//=============================================================================
void EventMessage::SetEventMessage(const std::string &message, int &cnt)
{
	//��x���Z�b�g����
	Reset();

	//���b�Z�[�W�J�E���g���Z�b�g
	messageSetCnt = cnt;

	//�e�L�X�g�Ƀ��b�Z�[�W���Z�b�g
	text->SetText(message);

	//�Đ���ԂɈڍs
	isPlaying = true;
}
