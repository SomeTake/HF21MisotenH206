//=============================================================================
//
// AI���x���r���A�[���� [LevelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "LevelViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/CircleGauge.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�����̏����T�C�Y
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(140.0f, 140.0f, 0.0f);

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
LevelViewer::LevelViewer()
{
	isPlaying = true;

	//����
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png");
	num->size = initNumSize;
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.80f, SCREEN_HEIGHT / 10 * 1.30f, 0.0f);
	num->intervalPosScr = 65.0f;
	num->intervalPosTex = 0.1f;
	num->placeMax = 4;
	num->baseNumber = 10;
	num->MakeVertex();

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/BG.png");
	bg->size = D3DXVECTOR3(250.0f, 250.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f);
	bg->MakeVertex();

	//�~�Q�[�W
	circleGuage = new CircleGauge(D3DXVECTOR2(250.0f, 250.0f));
	circleGuage->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
	circleGuage->SetScale(D3DXVECTOR3(1.0f, 1.0f, 0.0f));
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
	//���݂̃t���[���̃p�����[�^�Ƃ��ăZ�b�g
	currentParam[LevelAI] = (int)parameterBox[LevelAI];

	//�`��pratioLevel�ݒ�
	SetDrawingRatioLevel();

	//�����z�b�s���O����
	HopNumber();

	//�O�t���[���̃p�����[�^�Ƃ��ăZ�b�g
	lastParam[LevelAI] = (int)parameterBox[LevelAI];
}

//=============================================================================
// �`�揈��
//=============================================================================
void LevelViewer::Draw(void)
{
	if (!isPlaying)
		return;

	//�w�i���ɕ`��
	bg->Draw();

	//�~�Q�[�W
	circleGuage->SetPercent(drawingRatioLevel);
	circleGuage->Draw();

	//���F
	num->DrawCounter(num->baseNumber, (int)parameterBox[LevelAI], num->placeMax,
		num->intervalPosScr, num->intervalPosTex);
}

//=============================================================================
// �����z�b�s���O����
//=============================================================================
void LevelViewer::HopNumber(void)
{
	//�����̃z�b�v��
	const float hopNumValue = 50.0f;

	//�O�t���[����LevelAI��茻�݂�LevelAI���傫���ꍇ�z�b�s���O��Ԃɂ���
	if (currentParam[LevelAI] - lastParam[LevelAI] > 0)
	{
		num->isHopped = true;
	}

	//�z�b�s���O����
	num->size.y = num->HopNumber(num->size.y, initNumSize.y, hopNumValue);
}

//=============================================================================
// �`��pratioLevel�ݒ菈��
//=============================================================================
void LevelViewer::SetDrawingRatioLevel(void)
{
	//�O�t���[����LevelAI��茻�݂�LevelAI���傫���ꍇ
	if (currentParam[LevelAI] - lastParam[LevelAI] > 0)
	{
		if (isLevelAI_Decreasing)
		{
			isLevelAI_Decreasing = false;
		}
		isLevelAI_Increasing = true;
	}

	//�`��pRatioLevel����
	IncreaseDrawingRatioLevel();

	//�O�t���[����Level��茻�݂�LevelAI���������ꍇ
	if (currentParam[LevelAI] - lastParam[LevelAI] < 0)
	{
		if (isLevelAI_Increasing)
		{
			isLevelAI_Increasing = false;
		}

		isLevelAI_Decreasing = true;
	}

	//�`��pRatioLevel����
	DecreaseDrawingRatioLevel();
}

//=============================================================================
// �`��pratiolevel��������
//=============================================================================
void LevelViewer::IncreaseDrawingRatioLevel(void)
{
	//LevelAI���������Ȃ���s
	if (!isLevelAI_Increasing) return;

	//ratioLevel�̑����X�s�[�h
	const float ratioIncreaseSpeed = 0.005f;

	//�`��pRatioLevel�̕���RatioLevel��菬�����ԁA�`��pRatioLevel�𑝉�
	if (drawingRatioLevel < parameterBox[RatioLevel])
	{
		drawingRatioLevel += ratioIncreaseSpeed;
		if (drawingRatioLevel >= parameterBox[RatioLevel])
		{
			drawingRatioLevel = parameterBox[RatioLevel];
			isLevelAI_Increasing = false;
		}
	}

	//���������
	if (drawingRatioLevel > parameterBox[RatioLevel])
	{
		if (drawingRatioLevel < 1.0f)
		{
			drawingRatioLevel += ratioIncreaseSpeed;
		}
		else
		{
			drawingRatioLevel = 0.0f;
		}
	}
}

//=============================================================================
// �`��pratiolevel��������
//=============================================================================
void LevelViewer::DecreaseDrawingRatioLevel(void)
{
	//LevelAI���������Ȃ���s
	if (!isLevelAI_Decreasing) return;

	//ratioLevel�̌����X�s�[�h
	const float ratioDecreaseSpeed = 0.05f;

	//�`��pRatioLevel�̕���RatioLevel���傫���ԁA�`��pRatioLevel������
	if (drawingRatioLevel > parameterBox[RatioLevel])
	{
		drawingRatioLevel -= ratioDecreaseSpeed;
		if (drawingRatioLevel <= parameterBox[RatioLevel])
		{
			drawingRatioLevel = parameterBox[RatioLevel];
			isLevelAI_Decreasing = false;
		}
	}

	//���������
	if (drawingRatioLevel < parameterBox[RatioLevel])
	{
		if (drawingRatioLevel > 0.0f)
		{
			drawingRatioLevel -= ratioDecreaseSpeed;
		}
		else
		{
			drawingRatioLevel = 1.0f;
		}
	}
}
