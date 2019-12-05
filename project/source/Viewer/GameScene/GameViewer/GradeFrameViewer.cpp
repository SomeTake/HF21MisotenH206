//=============================================================================
//
// �O���[�h�t���[���N���X [GradeFrameViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../../main.h"
#include "GradeFrameViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Task/TaskManager.h"



//=============================================================================
// �R���X�g���N�^
//=============================================================================
GradeFrameViewer::GradeFrameViewer(void) :
	Callback(nullptr)
{
	isPlaying = true;

	FrameUp = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 128.0f), false);
	FrameUp->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/GradeFrame.png");
	FrameUp->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 64.0f, 0.0f));

	FrameDown = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 128.0f), false);
	FrameDown->LoadTexture("data/TEXTURE/Viewer/GameViewer/GradeUpViewer/GradeFrame.png");
	FrameDown->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT - 64.0f, 0.0f));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
GradeFrameViewer::~GradeFrameViewer()
{
	SAFE_DELETE(FrameUp);
	SAFE_DELETE(FrameDown);
}

//=============================================================================
// �X�V
//=============================================================================
void GradeFrameViewer::Update()
{
	if (!isPlaying)
		return;

	FrameUp->Update();
	FrameDown->Update();
}

//=============================================================================
// �`��
//=============================================================================
void GradeFrameViewer::Draw()
{
	if (!isPlaying)
		return;

	FrameUp->Draw();
	FrameDown->Draw();
}

//=============================================================================
// �X���C�h��ݒu����
//=============================================================================
void GradeFrameViewer::SlideIn(std::function<void(void)> callback)
{
	Callback = callback;

	FrameUp->Expand(60.0f, ExpandType::ExpandUpToDown);
	FrameDown->Expand(60.0f, ExpandType::ExpandDownToUp);

	TaskManager::Instance()->CreateDelayedTask(150, [&]()
	{
		SlideOut();
	});
}


//=============================================================================
// �X���C�h�A�E�g��ݒu����
//=============================================================================
void GradeFrameViewer::SlideOut(std::function<void(void)> callback)
{
	Callback = callback;

	FrameUp->Close(60.0f, CloseType::CloseDownToUp);
	FrameDown->Close(60.0f, CloseType::CloseUpToDown);
}

