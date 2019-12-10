//=============================================================================
//
// ���ʃr���A�[�R���g���[������ [ResultViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../ResultViewer/ResultScoreViewer.h"
#include "../ParameterContainer/ResultViewerParam.h"
#include "ResultViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ResultViewer::ResultViewer()
{
	viewerParam = new ResultViewerParam();
	resultViewer.push_back(scoreViewer = new ResultScoreViewer());
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ResultViewer::~ResultViewer()
{
	SAFE_DELETE(viewerParam);

	//�����������
	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		SAFE_DELETE(resultViewer[i]);
	}

	//�C���X�^���X����ꂽ�z����N���A
	resultViewer.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void ResultViewer::Update()
{
	if (!isActive)
		return;

	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		resultViewer[i]->Update();
	}
#ifdef _DEBUG
	if (Keyboard::GetTrigger(DIK_1))
	{
		scoreViewer->SetTelopIn([=]
		{
		});
	}
	if (Keyboard::GetTrigger(DIK_4))
	{
		scoreViewer->SetTelopOut();
	}
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void ResultViewer::Draw(void)
{
	if (!isActive)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		resultViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �p�����[�^�󂯎�鏈��
//=============================================================================
void ResultViewer::ReceiveParam(int cityScore, int worldScore, int spaceScore)
{
	int param[ResultViewerParam::fieldTypeMax] = { cityScore ,worldScore ,spaceScore };

	for (int i = 0; i < ResultViewerParam::fieldTypeMax; i++)
	{
		//�R���e�i�ɓ����
		viewerParam->score[i] = param[i];

		//�R���e�i����r���A�[�ɓn��
		scoreViewer->parameterBox[i] = viewerParam->score[i];
	}
}

//=============================================================================
// �`��۔���̃Z�b�g����
//=============================================================================
void ResultViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=============================================================================
// �`��۔���̃Q�b�g����
//=============================================================================
bool ResultViewer::GetIsActive()
{
	return isActive;
}

//=============================================================================
// ���U���g�X�R�A�r���A�[�̃C������
//=============================================================================
void ResultViewer::InResultScoreViewer(std::function<void()> CallbackInFin)
{
	scoreViewer->SetTelopIn(CallbackInFin);
}

//=============================================================================
// ���U���g�X�R�A�r���A�[�̃A�E�g����
//=============================================================================
void ResultViewer::OutResultScoreViewer()
{
	scoreViewer->SetTelopOut();
}