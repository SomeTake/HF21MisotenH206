//=====================================
//
// �^�C�g���r���A�[[TitleViewer.cpp]
// �@�\�F�^�C�g�����UI�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "TitleViewer.h"
#include "TitleLogo.h"
#include "SelectViewer.h"

//=====================================
// �R���X�g���N�^
//=====================================
TitleViewer::TitleViewer()
{
	logo = new TitleLogo();
	selectViewer = new SelectViewer();
}

//=====================================
// �f�X�g���N�^
//=====================================
TitleViewer::~TitleViewer()
{
	SAFE_DELETE(logo);
	SAFE_DELETE(selectViewer);
}

//=====================================
// �X�V
//=====================================
void TitleViewer::Update()
{
	logo->Update();
	selectViewer->Update();
}

//=====================================
// �`��
//=====================================
void TitleViewer::Draw()
{
	if (!isActive)
		return;

	logo->Draw();

	// �ʃE�C���h�E���쐬����̂ōŌ�
	selectViewer->Draw();
}

//=====================================
// �`��ۃt���O�̃Z�b�g
//=====================================
void TitleViewer::SetActive(bool flag)
{
	isActive = flag;
}
