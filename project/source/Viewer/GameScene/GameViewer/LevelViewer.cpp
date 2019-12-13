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

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

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
	num = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.80f, SCREEN_HEIGHT / 10 * 1.30f),D3DXVECTOR2(initNumSize.x, initNumSize.y), 
		"data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png", 65.0f, 0.1f, 4);

	//�I�[�o�[�t���[�p�̐���
	overflowNum = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.90f, SCREEN_HEIGHT / 10 * 2.20f), D3DXVECTOR2(initNumSize.x/2, initNumSize.y/2),
		"data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png", 35.0f, 0.1f, 6);

	//�w�i
	bg = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.20f),
		D3DXVECTOR2(250.0f, 250.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/BG.png");

	//�e�L�X�g
	text = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 0.60f),
		D3DXVECTOR2(180.0f, 49.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/Text.png");

	//�ʂ̊�����
	place = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * 9.90f, SCREEN_HEIGHT / 10 * 1.20f),
		D3DXVECTOR2(100.0f, 100.0f), "data/TEXTURE/Viewer/GameViewer/LevelViewer/PlaceText.png");
	place->SetTexture(2, 2, 0);

	//�~�Q�[�W
	for (int i = 0; i < guageMax; i++)
	{
		circleGuage[i] = new CircleGauge(D3DXVECTOR2(250.0f, 250.0f));
		circleGuage[i]->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/CircleGuage.png");
		circleGuage[i]->SetScale(D3DXVECTOR3(1.0f, 1.0f, 0.0f));
		circleGuage[i]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 9.30f, SCREEN_HEIGHT / 10 * 1.2f, 0.0f));
		circleGuage[i]->SetFillStart(circleGuage[i]->Top);
		circleGuage[i]->SetPercent(0.0f);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
LevelViewer::~LevelViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(overflowNum);
	SAFE_DELETE(bg);
	SAFE_DELETE(text);
	SAFE_DELETE(place);
	for (int i = 0; i < guageMax; i++)
	{
		SAFE_DELETE(circleGuage[i]);
	}
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

#ifdef _DEBUG
	Debug::Begin("LevelViewer");
	Debug::Text("AILevel:%f", parameterBox[LevelAI]);
	Debug::Text("currentFieldLevel:%f", parameterBox[CurrentFieldLevel]);
	Debug::End();
#endif

	//�Q�[�W������
	if ((int)parameterBox[CurrentFieldLevel] == 0)
	{
		for (int i = 0; i < guageMax; i++)
		{
			if (i == 0)continue;
			circleGuage[i]->SetPercent(0.0f);
		}
	}
	circleGuage[(int)parameterBox[CurrentFieldLevel]]->SetPercent(drawingRatioLevel);
}

//=============================================================================
// �`�揈��
//=============================================================================
void LevelViewer::Draw(void)
{
	if (!isPlaying) return;

	//�w�i���ɕ`��
	bg->Draw();

	for (int i = 0; i < guageMax; i++)
	{
		circleGuage[i]->SetScale(D3DXVECTOR3(1.0f - (0.10f*(parameterBox[CurrentFieldLevel] - i)),
			1.0f - (0.10f*(parameterBox[CurrentFieldLevel] - i)), 0.0f));
		circleGuage[i]->Draw();
	}

	num->DrawCounter(num->baseNumber, (int)parameterBox[LevelAI], num->placeMax,
		num->intervalPosScr, num->intervalPosTex);

	text->Draw();

	//�I�[�o�[�t���[���Ȃ�`��i�������j
	if (IsOverflowed())
	{
		overflowNum->DrawCounter(overflowNum->baseNumber, (int)parameterBox[LevelAI]-9999,
			overflowNum->intervalPosScr, overflowNum->intervalPosTex);
	}
	//place->Draw();
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

//=============================================================================
//�@�I�[�o�[�t���[���Ă邩�ǂ�����Ԃ�����
//=============================================================================
bool LevelViewer::IsOverflowed(void)
{
	//�F�����x����AI���x����9999�𒴂�����I�[�o�[�t���[����
	return (parameterBox[CurrentFieldLevel] == 2) && (parameterBox[LevelAI]>9999);
}
