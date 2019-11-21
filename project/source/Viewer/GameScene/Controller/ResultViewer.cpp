//=============================================================================
//
// ���ʃr���A�[�R���g���[������ [ResultViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../ResultViewer/ResultRankingViewer.h"
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
	resultViewer.push_back(rankingViewer = new ResultRankingViewer());
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ResultViewer::~ResultViewer()
{
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
	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		resultViewer[i]->Update();
	}
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
// �p�����[�^�󂯎�菈��
//=============================================================================
void ResultViewer::ReceiveParam(ResultViewerParam &param)
{

}

//=============================================================================
// �`��۔���̃Z�b�g
//=============================================================================
void ResultViewer::SetActive(bool flag)
{
	isActive = flag;
}
