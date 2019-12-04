//=============================================================================
//
// �����N���x���A�b�v�r���A�[���� [LinkLevelUpViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "LinkLevelUpViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
LinkLevelUpViewer::LinkLevelUpViewer() :
	Callback(nullptr)
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Text.png");
	text->size = D3DXVECTOR3(750.0f, 140.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT / 3 * 2, 0.0f);
	text->MakeVertex();
	text->SetAlpha(0.0f);

	//���j��
	laurel = new BaseViewerDrawer();
	laurel->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Laurel.png");
	laurel->size = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	laurel->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	laurel->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/2/1.5, 0.0f);
	laurel->MakeVertex();
	laurel->SetAlpha(0.0f);

	//����
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Number.png");
	num->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT / 2/1.5, 0.0f);
	num->intervalPosScr = 70.0f;
	num->intervalPosTex = 0.1f;
	num->placeMax = 2;
	num->baseNumber = 10;
	num->MakeVertex();
	num->SetAlpha(0.0f);

	//�{
	plus = new BaseViewerDrawer();
	plus->LoadTexture("data/TEXTURE/Viewer/FieldViewer/LinkLevelUpViewer/Plus.png");
	plus->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	plus->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	plus->position = D3DXVECTOR3(SCREEN_CENTER_X - num->intervalPosScr, SCREEN_HEIGHT / 2 / 1.5, 0.0f);
	plus->MakeVertex();
	plus->SetAlpha(0.0f);

	//�A�j���[�V����
	for (int i = 0; i < AnimLayer::Max; i++)
	{
		anim[i] = new ViewerAnimater();
	}

	std::vector<std::function<void()>> textVec = {
	[=] {
		//�e�L�X�g���X�N���[���C��
		anim[Text]->Move(*text, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT / 3 * 2), D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), 15.0f, OutCubic,[=]
		{
			//�T�u�A�j���[�V�����Ńt�F�[�h�C��
			anim[Text]->SubFade(*text, 0.0f, 1.0f,0.50f,OutCirc);
		});
	},
	[=] {
		//�e�L�X�g�ҋ@
		anim[Text]->Wait(30.0f);
	},
	[=] {
		//�e�L�X�g���X�N���[���A�E�g
		anim[Text]->Move(*text, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_HEIGHT/3), 15.0f, InCubic,[=]
		{
			//�T�u�A�j���[�V�����Ńt�F�[�h�A�E�g
			anim[Text]->SubFade(*text, 1.0f, 0.0f,1.0f,InCubic);
		});
	} };

	std::vector<std::function<void()>> bgVec = {
	[=] {
		//�������X�P�[��
		anim[BG]->Scale(*num,D3DXVECTOR2(0.0f, 0.0f),D3DXVECTOR2(100.0f, 100.0f),15.0f,OutBack,[=]
		{
			//�w�i�o��
			AppearBG();
		});
	},
	[=]{
		//�ҋ@
		anim[BG]->Wait(45.0f,[=]
		{
			//�w�i����
			DisAppearBG();
		});
	}
	};

	anim[Text]->SetAnimBehavior(textVec);
	anim[BG]->SetAnimBehavior(bgVec);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
LinkLevelUpViewer::~LinkLevelUpViewer()
{
	SAFE_DELETE(text);
	SAFE_DELETE(laurel);
	SAFE_DELETE(plus);
	SAFE_DELETE(num);
	for (int i = 0; i < AnimLayer::Max; i++)
	{
		SAFE_DELETE(anim[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void LinkLevelUpViewer::Update()
{
	if (!isPlaying) return;

	//�A�j���[�V�����Đ�
	anim[Text]->PlayAnim([=]
	{
		anim[Text]->SetPlayFinished(isPlaying, Callback);
	});
	anim[BG]->PlayAnim(nullptr);
}

//=============================================================================
// �`�揈��
//=============================================================================
void LinkLevelUpViewer::Draw(void)
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	//���j�����ɕ`��
	laurel->Draw();

	//���F�i0��`�悵�Ȃ��ł����j
	num->DrawCounterLeft(num->baseNumber, parameterBox,
		num->intervalPosScr, num->intervalPosTex);

	//�{
	plus->Draw();
	
	//�e�L�X�g
	text->Draw();
}

//=============================================================================
// �w�i�o������
//=============================================================================
void LinkLevelUpViewer::AppearBG()
{
	anim[BG]->SubFade(*plus, 0.0f, 1.0f, 0.50f, OutBack);
	anim[BG]->SubFade(*laurel, 0.0f, 1.0f, 0.50f, OutBack);
	anim[BG]->SubFade(*num, 0.0f, 1.0f, 0.50f, OutBack);
}

//=============================================================================
// �w�i��������
//=============================================================================
void LinkLevelUpViewer::DisAppearBG()
{
	anim[BG]->SubFade(*plus, 1.0f, 0.0f, 0.50f, OutBack);
	anim[BG]->SubFade(*laurel, 1.0f, 0.0f, 0.50f, OutBack);
	anim[BG]->SubFade(*num, 1.0f, 0.0f, 0.50f, OutBack);
}

//=============================================================================
// �����N���x���A�b�v�r���A�[�Z�b�g����
//=============================================================================
void LinkLevelUpViewer::Set(int level, std::function<void()> callback)
{
	//�p�����[�^���󂯎��
	parameterBox = level;

	anim[Text]->ResetAnim();
	anim[BG]->ResetAnim();

	//�Đ���Ԃɂ���
	isPlaying = true;

	this->Callback = callback;
}