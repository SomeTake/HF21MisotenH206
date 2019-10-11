//=============================================================================
//
// Game�r���A�[�Ǘ����� [GameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "StockViewer.h"
#include "TimerViewer.h"
#include "LevelViewer.h"
#include "GameViewerParam.h"
#include "GameViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
GameViewer::GameViewer()
{
	baseViewer.push_back(stockViewer = new StockViewer());
	baseViewer.push_back(timerViewer = new TimerViewer());
	baseViewer.push_back(levelViewer = new LevelViewer());

	baseViewerMax = baseViewer.size();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
GameViewer::~GameViewer()
{
	baseViewer.clear();

	SAFE_DELETE(stockViewer);
	SAFE_DELETE(timerViewer);
	SAFE_DELETE(levelViewer);
}

//=============================================================================
// �X�V����
//=============================================================================
void GameViewer::Update()
{
	for (int i = 0; i < baseViewerMax; i++)
	{
		baseViewer[i]->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void GameViewer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);

	for (int i = 0; i < baseViewerMax; i++)
	{
		baseViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �p�����[�^�󂯎�菈��
//=============================================================================
void GameViewer::ReceiveParam(GameViewerParam&param)
{
	//�X�g�b�N�r���A�[
	stockViewer->parameterBox[stockViewer->Bridge] = param.stockBuildItem;
	stockViewer->parameterBox[stockViewer->Drill] = param.stockBreakItem;
	stockViewer->parameterBox[stockViewer->EDF] = param.stockEDF;
	stockViewer->parameterBox[stockViewer->Insurance] = param.stockInsurance;

	//�^�C�}�[�r���A�[
	timerViewer->parameterBox = param.remainTime;

	//AI���x���r���A�[
	levelViewer->levelAI_Box = param.levelAI;
	levelViewer->ratioLevelBox = param.ratioLevel;
}
