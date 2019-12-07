//=============================================================================
//
// ���ʃX�R�A�r���A�[���� [ResultScoreViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "ResultScoreViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static const D3DXVECTOR2 scoreTextGapPos = D3DXVECTOR2(300.0f,-40.0f);
static const D3DXVECTOR2 rewardTextGapPos = D3DXVECTOR2(300.0f, 35.0f);
static const float fieldTelopGapPos = 200.0f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ResultScoreViewer::ResultScoreViewer() :
	parameterBox(),
	score(),
	completeRewardNum()
{
	//���Đ��J�n
	isPlaying = true;

	const float intervalPosTelop = 240.0f;
	const float intervalPosNum = 320.0f;
	const D3DXCOLOR telopColor[telopMax] = {
		D3DXCOLOR(0.0f, 104 / 255.0f, 98 / 255.0f, 0.9f),
		D3DXCOLOR(118/255.0f,0.0f,0.0f,0.9f),
		D3DXCOLOR(118/255.0f,106/255.0f,0.0f,0.9f),
		D3DXCOLOR(0.0f,59/255.0f,104/255.0f,0.9f),
	};

	for (int i = 0; i < telopMax; i++)
	{
		bg[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2,SCREEN_HEIGHT / 10 * 2.0f +i*intervalPosTelop),
			D3DXVECTOR2(1600.0f, 160.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/ScoreBG.png");
		bg[i]->SetColor(telopColor[i]);

		fieldText[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2, bg[i]->position.y-120.0f),
			D3DXVECTOR2(1024 / 2.0f, 1024 / 8.0f),"data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/FieldText.png");
		fieldText[i]->SetTexture(1, 4,i);

		scoreText[i] = new TextViewer("data/FONT/Makinas-4-Square.otf", 70);
		scoreText[i]->SetPos((int)(SCREEN_WIDTH / 10 * (1 + 0.5f*i) + 100.0f) - SCREEN_WIDTH, (int)(bg[i]->position.y - 40.0f));

		rewardText[i] = new TextViewer("data/FONT/Makinas-4-Square.otf", 70);
		rewardText[i]->SetPos((int)(SCREEN_WIDTH / 10 * (1 + 0.5f*i)+100.0f) - SCREEN_WIDTH, (int)(bg[i]->position.y + 40.0f));
	}

	anim = new ViewerAnimater();
	std::vector<std::function<void()>> vec = {
		[=] {
		//�V�e�B�e���b�v�X�N���[���C��
		InCityTelop();
	},
		[=] {
		//���[���h�e���b�v�X�N���[���C��
		InWorldTelop();	
	},
		[=] {
		//�X�y�[�X�e���b�v�X�N���[���C��
		InSpaceTelop();	
	},
		[=] {
		//���U���g�e���b�v�X�N���[���C��
		InResultTelop();	
	}};
	anim->SetAnimBehavior(vec);

	//city
	score[0] = parameterBox[0];
	//world
	score[1] = parameterBox[1];
	//space
	score[2] = parameterBox[2]%99990000;
	//overflow
	score[3] = (int)parameterBox[2]/10000;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ResultScoreViewer::~ResultScoreViewer()
{
	for (int i = 0; i < telopMax; i++)
	{
		SAFE_DELETE(bg[i]);
		SAFE_DELETE(fieldText[i]);
		SAFE_DELETE(rewardText[i]);
		SAFE_DELETE(scoreText[i]);
	}
	SAFE_DELETE(anim);
}

//=============================================================================
// �X�V����
//=============================================================================
void ResultScoreViewer::Update(void)
{
	if (!isPlaying) return;

	SetText();
	anim->PlayAnim([=]
	{
		anim->SetPlayFinished(isPlaying);
	});
}

//=============================================================================
// �`�揈��
//=============================================================================
void ResultScoreViewer::Draw(void)
{
	for (int i = 0; i < telopMax; i++)
	{
		bg[i]->Draw();
		fieldText[i]->Draw();
		rewardText[i]->Draw();
		scoreText[i]->Draw();
	}
}

//=============================================================================
// �e���b�v�e�L�X�g�X�N���[���C������
//=============================================================================
void ResultScoreViewer::SetText()
{
	//�����ŃX�R�A��\���ł���悤�ɂ���
	for (int i = 0; i < telopMax; i++)
	{
		rewardText[i]->SetText("���сF0��");
	}
	scoreText[0]->SetText("9999��9999��9999��9999");
	scoreText[1]->SetText("�X�R�A�F9999");
	scoreText[2]->SetText("�X�R�A�F9999��");
	scoreText[3]->SetText("�X�R�A�F9999��");
}

//=============================================================================
// �V�e�B�e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::InCityTelop()
{
	const float telopPosX = SCREEN_WIDTH / 10.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 1;

	anim->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc,[=]
			{
				anim->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x+scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// ���[���h�e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::InWorldTelop()
{
	const float telopPosX = SCREEN_WIDTH / 10.0f*1.50f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 2;

	anim->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});
		}
		);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �X�y�[�X�e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::InSpaceTelop()
{
	const float telopPosX = SCREEN_WIDTH / 10.0f*2.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 3;

	anim->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// ���U���g�e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::InResultTelop()
{
	const float telopPosX = SCREEN_WIDTH / 10.0f*2.50f;	
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 0;

	anim->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX - fieldTelopGapPos*1.5f, fieldText[index]->position.y), OutCirc, [=]
		{
			anim->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});

		});
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x-300.0f), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x-300.0f), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::Set()
{
	isPlaying = true;
}
