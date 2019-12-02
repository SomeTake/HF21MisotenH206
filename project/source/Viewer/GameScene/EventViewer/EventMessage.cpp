//=============================================================================
//
// �C�x���g���b�Z�[�W���� [EventMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "EventMessage.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventMessage::EventMessage() :
	animArray()
{
	//�e�L�X�g
	text = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf",40);
	text->SetColor(SET_COLOR_NOT_COLORED);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 8.6), (int)(SCREEN_HEIGHT*1.5));

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventMessage/BG.png");
	bg->size = D3DXVECTOR3(560.0f, 104.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT*1.5f,0.0f);
	bg->MakeVertex();

	////�A�j���[�V����
	//anim = new ViewerAnimater();
	//SetAnimBehavior();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventMessage::~EventMessage()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
	//SAFE_DELETE(anim);
}

//=============================================================================
// �X�V����
//=============================================================================
void EventMessage::Update(void)
{
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�Đ�����
	Play();
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventMessage::Draw(void)
{
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�w�i���ɕ`��
	bg->Draw();

	//�e�L�X�g
	text->Draw();
}

//=============================================================================
// �Đ�����
//=============================================================================
void EventMessage::Play(void)
{
	//anim->PlayAnim([=]
	//{
	//	SetPlayFinished();
	//}
	//);

	text->SetPos((int)bg->GetPosition().x, (int)bg->GetPosition().y);
	text->SetColor(bg->GetColor());
}

//=============================================================================
// �A�j���[�V��������ݒ菈��
//=============================================================================
void EventMessage::SetAnimBehavior(void)
{
	//�r���A�[�̕\�����W�Ԋu
	const float intervalViewerPos = 100.0f;

	//animArray.push_back([=]
	//{
	//	anim->Move(*bg, D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT*1.5f), 
	//		D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos), 40, OutCubic);
	//}
	//);
	//animArray.push_back([=]
	//{
	//	anim->Wait(50.0f);
	//}
	//);
	//animArray.push_back([=]
	//{
	//	anim->Move(*bg, D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos), 
	//		D3DXVECTOR2(SCREEN_WIDTH*1.2f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos), 20, InOutCubic, [=]
	//	{
	//		anim->SubFade(*bg,1.0f,0.0f, InOutCubic);
	//	});
	//}
	//);
}

//=============================================================================
// �Đ��I������
//=============================================================================
bool EventMessage::SetPlayFinished(void)
{
	text->SetColor(SET_COLOR_NOT_COLORED);
	bg->SetColor(SET_COLOR_NOT_COLORED);

	return isPlaying = false;
}

//=============================================================================
// ���b�Z�[�W�Z�b�g����
//=============================================================================
void EventMessage::SetEventMessage(const std::string &message, int &cnt)
{
	//���b�Z�[�W�J�E���g���Z�b�g
	messageSetCnt = cnt;

	//�e�L�X�g�Ƀ��b�Z�[�W���Z�b�g
	text->SetText(message);

	//�Đ���ԂɈڍs
	isPlaying = true;
}

//=============================================================================
// �Đ���Ԏ擾����
//=============================================================================
bool EventMessage::GetIsPlaying(void)
{
	return isPlaying;
}
