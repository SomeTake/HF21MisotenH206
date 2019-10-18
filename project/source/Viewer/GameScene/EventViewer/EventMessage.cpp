//=============================================================================
//
// �C�x���g���b�Z�[�W���� [EventMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "EventMessage.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventMessage::EventMessage()
{
	//�e�L�X�g
	text = new TextViewer("cinecaption", 50);

	////�w�i
	//bg = new BaseViewerDrawer();
	////bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/EventMessage/BG.png");
	//bg->MakeVertex();
	//bg->size = D3DXVECTOR3(204.80f, 51.20f, 0.0f);
	//bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.3, SCREEN_HEIGHT / 10 * 1.0f, 0.0f);
	//bg->SetColor(SET_COLOR_NOT_COLORED);

	//isPlaying = false;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventMessage::~EventMessage()
{
	SAFE_DELETE(text);
	//SAFE_DELETE(bg);
}

//=============================================================================
// �X�V����
//=============================================================================
void EventMessage::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventMessage::Draw(void)
{
	////�w�i���ɕ`��
	//bg->Draw();
	//bg->SetVertex();

	text->Draw();
}

//=============================================================================
// ���b�Z�[�W�Z�b�g����
//=============================================================================
void EventMessage::SetEventMessage(const std::string Message)
{
	text->SetText(Message);
	text->SetPos(1600, 900);
}
