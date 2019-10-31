//=============================================================================
//
// Game�r���A�[�Ǘ����� [GameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "ItemStockViewer.h"
#include "TimerViewer.h"
#include "LevelViewer.h"
#include "GameViewerParam.h"
#include "GameViewer.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
GameViewer::GameViewer()
{
	gameViewer.push_back(stockViewer = new ItemStockViewer());
	gameViewer.push_back(timerViewer = new TimerViewer());
	gameViewer.push_back(levelViewer = new LevelViewer());

	gameViewerMax = gameViewer.size();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
GameViewer::~GameViewer()
{
	//�C���X�^���X����ꂽ�z����N���A
	gameViewer.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void GameViewer::Update()
{
	for (int i = 0; i < gameViewerMax; i++)
	{
		gameViewer[i]->Update();
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

	for (int i = 0; i < gameViewerMax; i++)
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
	if (stockViewer->InBanStock == false && stockViewer->InBanStock != param.InBanStock)
	{
		stockViewer->BanIconDebut = true;
	}
	stockViewer->InBanStock = param.InBanStock;

	//�^�C�}�[�r���A�[
	timerViewer->parameterBox = param.remainTime;

	//AI���x���r���A�[
	levelViewer->parameterBox[levelViewer->LevelAI] = (float)param.levelAI;
	levelViewer->parameterBox[levelViewer->RatioLevel] = param.ratioLevel;
}
