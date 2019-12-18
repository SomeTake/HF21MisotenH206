//=============================================================================
//
// �C�x���g���b�Z�[�W���� [EventMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "EventMessage.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventMessage::EventMessage()
{
	//�e�L�X�g
	text = new TextViewer("���˂���Ղ����",40);
	text->SetColor(SET_COLOR_NOT_COLORED);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 8.6), (int)(SCREEN_HEIGHT*1.5));

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventMessage/BG.png");
	bg->size = D3DXVECTOR3(600.0f, 104.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.4f, SCREEN_HEIGHT*1.5f,0.0f);
	bg->MakeVertex();

	//�A�j���[�V����
	anim = new ViewerAnimater();
	const float intervalViewerPos = 100.0f;

	std::vector<std::function<void()>> vec = {
	[=] {
		//�w�i���X�N���[���C��
		anim->Move(*bg, D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT*1.5f),
			D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos), 40, OutCubic);
	},
	[=] {
		//�ҋ@
		anim->Wait(50.0f);
	},
	[=] {
		//�w�i���X�N���[���A�E�g
		anim->Move(*bg, D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos),
			D3DXVECTOR2(SCREEN_WIDTH*1.2f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos), 20, InOutCubic, [=]
		{
			//�T�u�A�j���[�V�����Ńt�F�[�h�A�E�g
			anim->SubFade(*bg,1.0f,0.0f,1.5f, InOutCubic);
		});
	} };

	anim->SetAnimBehavior(vec);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventMessage::~EventMessage()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
	SAFE_DELETE(anim);
}

//=============================================================================
// �X�V����
//=============================================================================
void EventMessage::Update(void)
{
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	anim->PlayAnim([=]
	{
		anim->SetPlayFinished(isPlaying);
	});
	text->SetPos((int)bg->GetPosition().x, (int)bg->GetPosition().y);
	text->SetColor(bg->GetColor());
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
// �Đ���Ԏ擾����
//=============================================================================
bool EventMessage::GetIsPlaying(void)
{
	return isPlaying;
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

	//�J�n����
	text->SetColor(SET_COLOR_NOT_COLORED);
	bg->SetColor(SET_COLOR_NOT_COLORED);

	//�Đ���ԂɈڍs
	isPlaying = true;
}