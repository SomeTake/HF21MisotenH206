//=============================================================================
//
// �C�x���g�e���b�v���� [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "EventTelop.h"

#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventTelop::EventTelop():
	animArray(),
	isPlaying(false)
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

	//�A�j���[�V����
	anim = new ViewerAnimater();
	SetAnimBehavior();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventTelop::~EventTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
	SAFE_DELETE(anim);
}

//=============================================================================
// �X�V����
//=============================================================================
void EventTelop::Update()
{
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�A�j���[�V�����Đ�
	anim->PlayAnim(animArray, [=]
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
	//�A�j���[�V�����z��ɃA�j���[�V�������Z�b�g
	animArray.push_back([=]()
	{
		//�w�i�I�[�v��
		anim->Scale(*bg, D3DXVECTOR2(SCREEN_WIDTH, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, 128.0f), 15.0f, OutCirc);
	});
	animArray.push_back([=]()
	{
		//�e�L�X�g�X�N���[���C��
		anim->Move(*text, D3DXVECTOR2(SCREEN_WIDTH*1.5, SCREEN_CENTER_Y), D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), 50.0f, OutCirc);
	});
	animArray.push_back([=]()
	{
		//�ҋ@
		anim->Wait(5.0f);
	});
	animArray.push_back([=]()
	{
		//�e�L�X�g�X�N���[���A�E�g
		anim->Move(*text, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), D3DXVECTOR2(-SCREEN_WIDTH * 1.5, SCREEN_CENTER_Y), 30.0f, InCirc);
	});
	animArray.push_back([=]()
	{
		//�w�i�N���[�Y
		anim->Scale(*bg, D3DXVECTOR2(SCREEN_WIDTH, 128.0f), D3DXVECTOR2(SCREEN_WIDTH, 0.0f), 15.0f, OutCirc);
	});
}

//=============================================================================
// �A�j���[�V�����I������
//=============================================================================
bool EventTelop::SetPlayFinished(void)
{
	if (Callback != nullptr)
		Callback();

	return isPlaying = false;
}

//=============================================================================
// �e�N�X�`��UV�Z�b�g����
//=============================================================================
void EventTelop::SetTexture(TelopID id)
{
	//�e�L�X�g��UV��ύX
	text->SetTexture(1, Max, id);

	bool isNegative;

	if (id >= Meteorite) isNegative = true;
	else isNegative = false;

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
