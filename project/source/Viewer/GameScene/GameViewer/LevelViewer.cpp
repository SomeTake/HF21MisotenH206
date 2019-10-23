//=============================================================================
//
// AI���x���r���A�[���� [LevelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/CircleGauge.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "LevelViewer.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�����̃z�b�v��
static const float hopNumValue = 50.0f;

//�����̏����T�C�Y
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(70.0f, 70.0f, 0.0f);

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
LevelViewer::LevelViewer()
{
	//����
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png");
	num->MakeVertex();
	num->size = D3DXVECTOR3(70.0f, 70.0f, 0.0f);
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.80f, SCREEN_HEIGHT / 10 * 1.30f, 0.0f);
	num->SetColor(SET_COLOR_NOT_COLORED);
	num->intervalNumberScr = 65.0f;
	num->intervalNumberTex = 0.1f;
	num->placeMax = 4;
	num->baseNumber = 10;

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/BG.png");
	bg->MakeVertex();
	bg->size = D3DXVECTOR3(125.0f, 125.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);

	//�~�Q�[�W
	circleGuage = new CircleGauge(D3DXVECTOR2(125.0f, 125.0f));
	circleGuage->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
	circleGuage->SetScale(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	circleGuage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	circleGuage->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f));
	circleGuage->SetFillStart(circleGuage->Top);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
LevelViewer::~LevelViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(bg);
	SAFE_DELETE(circleGuage);
}

//=============================================================================
// �X�V����
//=============================================================================
void LevelViewer::Update(void)
{
	Animate();
}

//=============================================================================
// �`�揈��
//=============================================================================
void LevelViewer::Draw(void)
{
	//�w�i���ɕ`��
	bg->SetVertex();
	bg->Draw();

	circleGuage->SetPercent(parameterBox[RatioLevel]);
	circleGuage->Draw();

	num->DrawCounter(num->baseNumber, (int)parameterBox[LevelAI], num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);
}

//=============================================================================
// �A�j���[�V��������
//=============================================================================
void LevelViewer::Animate(void)
{
	//�O�t���[���̃p�����[�^��茻�݂̃p�����[�^���傫���ꍇ�z�b�s���O��Ԃɂ���
	currentParam = (int)parameterBox[LevelAI];
	if (currentParam - lastParam > 0)
	{
		num->isHopped = true;
	}
	lastParam = (int)parameterBox[LevelAI];

	//�z�b�s���O����
	num->size.y = num->HopNumber(num->size.y, initNumSize.y, hopNumValue);
}
