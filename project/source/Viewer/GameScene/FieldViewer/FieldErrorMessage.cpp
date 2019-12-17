//=============================================================================
//
// �t�B�[���h�G���[���b�Z�[�W���� [FieldErrorMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "FieldErrorMessage.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../../Sound/SoundConfig.h"
#include "../../../../Framework/Sound/SoundEffect.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
FieldErrorMessage::FieldErrorMessage()
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/FieldViewer/FieldErroMessage/Text.png");
	text->size = D3DXVECTOR3(640.0f, 80.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y*1.3f, 0.0f);
	text->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
FieldErrorMessage::~FieldErrorMessage()
{
	SAFE_DELETE(text);
}

//=============================================================================
// �X�V����
//=============================================================================
void FieldErrorMessage::Update(void)
{
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�t���[���X�V
	countFrame++;

	//���Ԃ��o�߂���
	if (countFrame >= 60.0f)
	{
		countFrame = 0;
		isPlaying = false;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void FieldErrorMessage::Draw(void)
{
	//�Đ����Ȃ���s
	if (!isPlaying) return;

	//�w�i���ɕ`��
	text->Draw();
}

//=============================================================================
// ���b�Z�[�W�Z�b�g����
//=============================================================================
void FieldErrorMessage::Set(ErroID id)
{
	//�e�N�X�`�����󂯓n������
	text->SetTexture(1, Max, id);

	//�Đ���ԂɈڍs
	isPlaying = true;

	SE::Play(SoundConfig::SEID::Error, 1.0f);
}
