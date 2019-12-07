//=============================================================================
//
// Game�r���A�[�Ǘ����� [GameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../GameViewer/ItemStockViewer.h"
#include "../GameViewer/TimerViewer.h"
#include "../GameViewer/LevelViewer.h"
#include "../GameViewer/GradeUpViewer.h"
#include "../GameViewer/GradeFrameViewer.h"
#include "../GameViewer/GradeNameViewer.h"
#include "../ParameterContainer/GameViewerParam.h"
#include "GameViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
GameViewer::GameViewer()
{
	gameViewer.push_back(stockViewer = new ItemStockViewer());
	gameViewer.push_back(timerViewer = new TimerViewer());
	gameViewer.push_back(levelViewer = new LevelViewer());
	gameViewer.push_back(gradeUpViewer = new GradeUpViewer());
	gameViewer.push_back(gradeFrameViewer = new GradeFrameViewer());
	gameViewer.push_back(gradeNameViewer = new GradeNameViewer());
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
GameViewer::~GameViewer()
{
	//�����������
	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		SAFE_DELETE(gameViewer[i]);
	}

	//�C���X�^���X����ꂽ�z����N���A
	gameViewer.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void GameViewer::Update()
{
	Debug::Begin("GradeUp");
	if (Debug::Button("GradeUp"))
		gradeUpViewer->SetGradeUp();
	if (Debug::Button("Slide"))
		gradeFrameViewer->SlideIn();
	if (Debug::Button("GradeTitle"))
		gradeFrameViewer->SlideIn([&]()
	{
		gradeNameViewer->SetGradeName(Field::World, [&]()
		{
			gradeFrameViewer->SlideOut();
		});
	});
	Debug::End();

	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		gameViewer[i]->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void GameViewer::Draw(void)
{
	if (!isActive)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		gameViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �p�����[�^�󂯎�菈��
//=============================================================================
void GameViewer::ReceiveParam(GameViewerParam &param)
{
	//�X�g�b�N�r���A�[
	stockViewer->parameterBox = param.stockNum;

	//�^�C�}�[�r���A�[
	timerViewer->parameterBox = param.remainTime;

	//AI���x���r���A�[
	levelViewer->parameterBox[levelViewer->LevelAI] = (float)param.levelAI;
	levelViewer->parameterBox[levelViewer->RatioLevel] = param.ratioLevel;
}

//=============================================================================
// �`��۔���̃Z�b�g
//=============================================================================
void GameViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=============================================================================
// ����r���[�A�`��۔���̃Z�b�g
//=============================================================================
void GameViewer::SetActive(bool flag, ViewerNo viewer)
{
	if (viewer != ItemStock)
	{
		gameViewer.at(viewer)->isPlaying = flag;
	}
	else
	{
		stockViewer->SetInDrawing(flag);
	}
}

//=============================================================================
// �O���[�h�A�b�v���o
//=============================================================================
void GameViewer::SetGradeUp(std::function<void(void)> Callback)
{
	// ���x���r���[�A�̕`����~
	SetActive(false, ViewerNo::Level);

	gradeUpViewer->SetGradeUp([=]()
	{
		// ���x���r���[�A�̕`��𕜋A
		SetActive(true, ViewerNo::Level);
		Callback();
	});
}

//=============================================================================
// �O���[�h�^�C�g�����o
//=============================================================================
void GameViewer::SetGradeTitle(int fieldLevel, std::function<void(void)> Callback)
{
	// ���x���r���[�A�̕`����~
	SetActive(false, ViewerNo::Level);
	SetActive(false, ViewerNo::ItemStock);
	SetActive(false, ViewerNo::Timer);

	gradeFrameViewer->SlideIn([=]()
	{
		gradeNameViewer->SetGradeName(fieldLevel, [=]()
		{
			gradeFrameViewer->SlideOut([=]()
			{
				SetActive(true, ViewerNo::Level);
				SetActive(true, ViewerNo::ItemStock);
				SetActive(true, ViewerNo::Timer);
				Callback();
			});
		});
	});
}
