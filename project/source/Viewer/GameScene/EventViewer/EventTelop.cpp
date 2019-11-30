//=============================================================================
//
// �C�x���g�e���b�v���� [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "EventTelop.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventTelop::EventTelop()
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventTelop/Text/Text.png");
	text->size = D3DXVECTOR3(1024, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_WIDTH*1.5, SCREEN_CENTER_Y, 0.0f);
	text->MakeVertex();

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventTelop/BG/BG.png");
	bg->size = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->MakeVertex();

	//�A�j���[�V�����̓����ݒ�
	SetAnimBehavior();
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
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�A�j���[�V�����Đ�
	ViewerAnimater::PlayAnim(animArray, [=]
	{
		SetPlayFinished();
	});
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventTelop::Draw(void)
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	//�w�i���ɕ`��
	bg->Draw();

	//�e�L�X�g
	text->Draw();
}

//=============================================================================
// �A�j���[�V�����̓���ݒ菈��
//=============================================================================
void EventTelop::SetAnimBehavior(void)
{
	//�A�j���[�V�����̐�
	const int animMax = 5;

	const D3DXVECTOR2 textStartPosition[animMax] =
	{
		D3DXVECTOR2(SCREEN_WIDTH*1.5,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_WIDTH*1.5,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),
		D3DXVECTOR2(-SCREEN_WIDTH * 1.5,SCREEN_CENTER_Y),
	};

	const D3DXVECTOR2 textEndPosition[animMax] =
	{
		D3DXVECTOR2(SCREEN_WIDTH*1.5,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),
		D3DXVECTOR2(-SCREEN_WIDTH * 1.5,SCREEN_CENTER_Y),
		D3DXVECTOR2(-SCREEN_WIDTH * 1.5,SCREEN_CENTER_Y),
	};

	const D3DXVECTOR2 bgStartSize[animMax] =
	{
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
	};

	const D3DXVECTOR2 bgEndSize[animMax] =
	{
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
	};


	//�e�L�X�g�A�j���[�V�������
	const EaseType animType[animMax] = {
		OutCirc,
		OutCirc,
		InOutCubic,
		InCirc,
		OutCirc
	};

	//�e�L�X�g�A�j���[�V�����Ԋu(������ύX����ƃA�j���[�V�����̑����𒲐��ł���)
	//*����(0������Ɩ�����ɂȂ邩��A�j���[�V�������̂��̂��폜���邱��)
	const float animDuration[animMax] = {
		15,
		50,
		5,
		30,
		15
	};

	//�A�j���[�V�����V�[��
	enum TelopAnimScene
	{
		BG_Open,
		Text_In,
		Text_Stop,
		Text_Out,
		BG_Close
	};

	//�A�j���[�V�����z��ɃA�j���[�V�������Z�b�g
	animArray.push_back([=]()
	{
		//�w�i�I�[�v��
		ViewerAnimater::Scale(*bg, bgStartSize[BG_Open], bgEndSize[BG_Open], animDuration[BG_Open], animType[BG_Open]);
	});
	animArray.push_back([=]()
	{
		//�e�L�X�g�X�N���[���C��
		ViewerAnimater::Move(*text, textStartPosition[Text_In], textEndPosition[Text_In], animDuration[Text_In], animType[Text_In]);
	});
	animArray.push_back([=]()
	{
		//�ҋ@
		ViewerAnimater::Wait(animDuration[Text_Stop]);
	});
	animArray.push_back([=]()
	{
		//�e�L�X�g�X�N���[���A�E�g
		ViewerAnimater::Move(*text, textStartPosition[Text_Out], textEndPosition[Text_Out], animDuration[Text_Out], animType[Text_Out]);
	});
	animArray.push_back([=]()
	{
		//�w�i�N���[�Y
		ViewerAnimater::Scale(*bg, bgStartSize[BG_Close], bgEndSize[BG_Close], animDuration[BG_Close], animType[BG_Close]);
	});
}

//=============================================================================
// �A�j���[�V�����I������
//=============================================================================
bool EventTelop::SetPlayFinished(void)
{
	if (Callback != nullptr)
	{
		//�Đ��I���̒ʒm
		Callback();
	}

	return isPlaying = false;
}

//=============================================================================
// �e�N�X�`�����󂯓n������
//=============================================================================
void EventTelop::SetTexture(TelopID id)
{
	//�e�L�X�g��UV��ύX
	text->SetTexture(1, Max, id);

	bool isNegative;

	if (id >= Meteorite)
	{
		isNegative = true;
	}
	else
	{
		isNegative = false;
	}

	//�w�i��UV��ύX
	bg->SetTexture(1, 2, isNegative);
	bg->vertexWk[1].tex.x = 3.0f;
	bg->vertexWk[3].tex.x = 3.0f;
}


//=============================================================================
// �e���b�v�Z�b�g����
//=============================================================================
void EventTelop::Set(TelopID id, std::function<void(void)> Callback)
{
	//�e�N�X�`�����󂯓n��
	SetTexture(id);

	//�Đ���Ԃɂ���
	isPlaying = true;

	//�e���b�v�Đ��I���ʒm
	this->Callback = Callback;
}
