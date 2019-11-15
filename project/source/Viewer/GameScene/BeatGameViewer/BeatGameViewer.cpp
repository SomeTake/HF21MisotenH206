//=============================================================================
//
// �A�ŃQ�[���r���A�[�Ǘ����� [BeatGameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "BeatTitleViewer.h"
#include "BeatGaugeViewer.h"
#include "BeatTimerViewer.h"
#include "BeatStarterViewer.h"
#include "BeatResultViewer.h"
#include "BeatGameViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
BeatGameViewer::BeatGameViewer()
{
	beatGameViewer.push_back(titleViewer = new BeatTitleViewer);
	beatGameViewer.push_back(gaugeViewer = new BeatGaugeViewer);
	beatGameViewer.push_back(timerViewer = new BeatTimerViewer);
	beatGameViewer.push_back(starterViewer = new BeatStarterViewer);
	beatGameViewer.push_back(resultViewer = new BeatResultViewer);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
BeatGameViewer::~BeatGameViewer()
{
	//�����������
	for (unsigned int i = 0; i < beatGameViewer.size(); i++)
	{
		SAFE_DELETE(beatGameViewer[i]);
	}

	//�C���X�^���X����ꂽ�z����N���A
	beatGameViewer.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void BeatGameViewer::Update()
{
	for (unsigned int i = 0; i < beatGameViewer.size(); i++)
	{
		beatGameViewer[i]->Update();
	}

#ifdef _DEBUG

	SetGameTitle(titleViewer->CalmAI);
	SetRemainTime(0);

	if (Keyboard::GetTrigger(DIK_R))
	{
		SetReady();
	}

	if (Keyboard::GetTrigger(DIK_G))
	{
		SetGo();
	}

	if (Keyboard::GetTrigger(DIK_3))
	{
		SetResult(resultViewer->Failed, nullptr);
	}

	if (Keyboard::GetTrigger(DIK_4))
	{
		SetResult(resultViewer->Success, nullptr);
	}

#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void BeatGameViewer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < beatGameViewer.size(); i++)
	{
		beatGameViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �A�ŃQ�[���̃^�C�g����ݒu���鏈��
//=============================================================================
void BeatGameViewer::SetGameTitle(BeatTitleViewer::TitleID id)
{
	titleViewer->Set(id);
}

//=============================================================================
// �A�ŃQ�[���̃Q�[�W��ݒu���鏈��
//=============================================================================
void BeatGameViewer::SetGameGauge(float percent)
{
	gaugeViewer->Set(percent);
}

//=============================================================================
// �A�ŃQ�[���̎c�莞�Ԃ�ݒ肷�鏈��
//=============================================================================
void BeatGameViewer::SetRemainTime(float time)
{
	timerViewer->Set(time);
}

//=============================================================================
// �uReady�v��\�����鏈��
//=============================================================================
void BeatGameViewer::SetReady(void)
{
	starterViewer->SetReady();
}

//=============================================================================
// �uGO�v��\�����鏈��
//=============================================================================
void BeatGameViewer::SetGo(void)
{
	starterViewer->SetGo();
}

//=============================================================================
// ���ʂ�\�����鏈��
//=============================================================================
void BeatGameViewer::SetResult(BeatResultViewer::ResultID id, std::function<void(void)> Callback)
{
	resultViewer->Set(id, Callback);
}
