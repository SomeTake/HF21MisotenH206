//=============================================================================
//
// �K�C�h�����o���r���A�[���� [GuideCallOutViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "GuideCallOutViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
GuideCallOutViewer::GuideCallOutViewer()
{
	//�e�L�X�g
	text = new TextViewer("data/TEXTURE/Viewer/GuideViewer/GuideCallOutViewer/Text_cinecaption226.ttf", 25);
	text->SetColor(SET_COLOR_BLACK);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 1.5f), (int)(SCREEN_HEIGHT/10*9.1f));

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GuideViewer/GuideCallOutViewer/CallOut.png");
	bg->size = D3DXVECTOR3(400.0f, 120.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 1.5), (float)(SCREEN_HEIGHT / 10 * 9), 0.0f);
	bg->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
GuideCallOutViewer::~GuideCallOutViewer()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// �X�V����
//=============================================================================
void GuideCallOutViewer::Update(void)
{
	//�Đ�����
	Play();
}

//=============================================================================
// �`�揈��
//=============================================================================
void GuideCallOutViewer::Draw(void)
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
void GuideCallOutViewer::Play(void)
{
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�Đ�����
	const int playTime = 3;

	//�t���[���X�V
	countFrame++;

	//�Đ����ԂɒB������Đ��I��
	if (countFrame >= playTime * 30)
	{
		countFrame = 0;

		isPlaying = false;
	}
}

//=============================================================================
// ���b�Z�[�W�Z�b�g����
//=============================================================================
void GuideCallOutViewer::Set(const std::string &message)
{
	//�e�L�X�g�Ƀ��b�Z�[�W���Z�b�g
	text->SetText(message);

	//�t���[���J�E���g�����Z�b�g
	countFrame = 0;

	//�Đ���ԂɈڍs
	isPlaying = true;
}
