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
#include "../ParameterContainer/GameViewerParam.h"
#include "GameViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
GameViewer::GameViewer()
{
	gameViewer.push_back(stockViewer = new ItemStockViewer());
	gameViewer.push_back(timerViewer = new TimerViewer());
	gameViewer.push_back(levelViewer = new LevelViewer());
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
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);

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
