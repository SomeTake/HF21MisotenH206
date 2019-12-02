//=============================================================================
//
// �A�ŃQ�[���X�^�[�^�[�r���A�[���� [BeatStarterViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "BeatStarterViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BeatStarterViewer::BeatStarterViewer():
	shouldReady(false),
	shouldGo(false)
{
	//���f�B�[�e�L�X�g
	readyText = new BaseViewerDrawer();
	readyText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatStarterViewer/Text.png");
	readyText->size = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
	readyText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	readyText->position = D3DXVECTOR3(SCREEN_WIDTH * 1.5f, SCREEN_CENTER_Y, 0.0f);
	readyText->MakeVertex();
	readyText->SetTexture(1, 2, 0);

	//�S�[�e�L�X�g
	goText = new BaseViewerDrawer();
	goText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatStarterViewer/Text.png");
	goText->size = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
	goText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	goText->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	goText->MakeVertex();
	goText->SetTexture(1, 2, 1);

	//�A�j���[�V����
	for (int i = 0; i < TextType::Max; i++)
	{
		anim[i] = new ViewerAnimater();
	}

	std::vector<std::function<void()>> readyVec = {
		[=] {
		anim[TextType::Ready]->Move(*readyText,D3DXVECTOR2(SCREEN_WIDTH * 1.5f,SCREEN_CENTER_Y),D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),15.0f,OutCirc);
		} };
	std::vector<std::function<void()>> goVec = {
		[=] {
		anim[TextType::Go]->Scale(*goText,D3DXVECTOR2(500.0f,0.0f),D3DXVECTOR2(500.0f,200.0f),10.0f,OutCirc);
		},
		[=] {
		anim[TextType::Go]->Wait(10.0f);
		}, 
		[=] {
		anim[TextType::Go]->Fade(*goText,1.0f,0.0f,1.0f,OutCirc);
		} };

	anim[TextType::Ready]->SetAnimBehavior(readyVec);
	anim[TextType::Go]->SetAnimBehavior(goVec);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BeatStarterViewer::~BeatStarterViewer()
{
	SAFE_DELETE(readyText);
	SAFE_DELETE(goText);
	for (int i = 0; i < TextType::Max; i++)
	{
		SAFE_DELETE(anim[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void BeatStarterViewer::Update()
{
	if (isPlaying&&shouldReady)
	{
		anim[TextType::Ready]->PlayAnim([=]
		{
			anim[TextType::Ready]->SetPlayFinished(isPlaying);
		});
	}
	if (isPlaying&&shouldGo)
	{
		anim[TextType::Go]->PlayAnim([=]
		{
			anim[TextType::Go]->SetPlayFinished(isPlaying);
		});
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void BeatStarterViewer::Draw(void)
{
	if(shouldReady)
		readyText->Draw();
	if(shouldGo)
		goText->Draw();
}

//=============================================================================
// ���f�B�[�e�L�X�g�Z�b�g����
//=============================================================================
void BeatStarterViewer::SetReady(void)
{
	//�S�[�e�L�X�g�������I�����Ă���Z�b�g
	shouldGo = false;
	isPlaying = true;
	shouldReady = true;
}

//=============================================================================
// �S�[�e�L�X�g�Z�b�g����
//=============================================================================
void BeatStarterViewer::SetGo(void)
{
	//���f�B�[�e�L�X�g�������I�����Ă���Z�b�g
	shouldReady = false;
	isPlaying = true;
	shouldGo = true;
}
