//=============================================================================
//
// �A�ŃQ�[�����ʃr���A�[���� [BeatResultViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "BeatResultViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BeatResultViewer::BeatResultViewer()
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatResultViewer/Text.png");
	text->size = D3DXVECTOR3(512.0f, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(-SCREEN_WIDTH * 1.5, SCREEN_CENTER_Y, 0.0f);
	text->MakeVertex();

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatResultViewer/BG.png");
	bg->size = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	bg->MakeVertex();

	//�A�j���[�V����
	anim = new ViewerAnimater();
	std::vector<std::function<void()>> vec = {
		[=] {
		//�w�i�I�[�v��
		anim->Scale(*bg, D3DXVECTOR2(SCREEN_WIDTH, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, 128.0f), 15.0f, OutCirc);
	},
		[=] {
		//�e�L�X�g�X�N���[���C��
		anim->Move(*text, D3DXVECTOR2(-SCREEN_WIDTH*1.5, SCREEN_CENTER_Y), D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), 50.0f, OutCirc);
	},
		[=] {
		//�ҋ@
		anim->Wait(5.0f);
	},
		[=] {
		//�e�L�X�g�X�N���[���A�E�g
		anim->Move(*text, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), D3DXVECTOR2(SCREEN_WIDTH * 1.5, SCREEN_CENTER_Y), 30.0f, InCirc);
	},
		[=] {
		//�w�i�N���[�Y
		anim->Scale(*bg, D3DXVECTOR2(SCREEN_WIDTH, 128.0f), D3DXVECTOR2(SCREEN_WIDTH, 0.0f), 15.0f, OutCirc);
	} };
	anim->SetAnimBehavior(vec);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BeatResultViewer::~BeatResultViewer()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
	SAFE_DELETE(anim);
}

//=============================================================================
// �X�V����
//=============================================================================
void BeatResultViewer::Update()
{
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�A�j���[�V�����Đ�
	anim->PlayAnim([=]
	{
		anim->SetPlayFinished(isPlaying, Callback);
	});
}

//=============================================================================
// �`�揈��
//=============================================================================
void BeatResultViewer::Draw(void)
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	//�w�i���ɕ`��
	bg->Draw();

	//�e�L�X�g
	text->Draw();
}

//=============================================================================
// �e�N�X�`�����󂯓n������
//=============================================================================
void BeatResultViewer::SetTexture(ResultID id)
{
	//�e�L�X�g��UV��ύX
	text->SetTexture(1, ResultID::Max, id);

	//�w�i��UV��ύX
	bg->SetTexture(1, ResultID::Max, id);
	bg->vertexWk[1].tex.x = 3.0f;
	bg->vertexWk[3].tex.x = 3.0f;
}

//=============================================================================
// ���ʃr���A�[�Z�b�g����
//=============================================================================
void BeatResultViewer::Set(ResultID id, std::function<void(void)> Callback)
{
	//�e�N�X�`�����󂯓n��
	SetTexture(id);

	//�Đ���Ԃɂ���
	isPlaying = true;

	//�e���b�v�Đ��I���ʒm
	this->Callback = Callback;
}
