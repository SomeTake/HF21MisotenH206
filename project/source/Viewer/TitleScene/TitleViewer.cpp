//=====================================
//
// �^�C�g���r���A�[[TitleViewer.cpp]
// �@�\�F�^�C�g�����UI�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "TitleViewer.h"
#include "TitleLogo.h"

//=====================================
// �R���X�g���N�^
//=====================================
TitleViewer::TitleViewer()
{
	logo = new TitleLogo();
}

//=====================================
// �f�X�g���N�^
//=====================================
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(logo)
}

//=====================================
// �X�V
//=====================================
void TitleViewer::Update()
{
	logo->Update();
}

//=====================================
// �`��
//=====================================
void TitleViewer::Draw()
{
	if (!isActive)
		return;

	logo->Draw();
}

//=====================================
// �`��ۃt���O�̃Z�b�g
//=====================================
void TitleViewer::SetActive(bool flag)
{
	isActive = flag;
}
