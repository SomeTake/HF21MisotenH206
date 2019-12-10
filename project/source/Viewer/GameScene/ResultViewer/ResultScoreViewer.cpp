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
	completeRewardNum(),
	isInPlaying(false),
	isOutPlaying(false)
{
	const D3DXCOLOR telopColor[telopMax] = {
		D3DXCOLOR(0.0f, 104 / 255.0f, 98 / 255.0f, 0.9f),
		D3DXCOLOR(118/255.0f,0.0f,0.0f,0.9f),
		D3DXCOLOR(118/255.0f,106/255.0f,0.0f,0.9f),
		D3DXCOLOR(0.0f,59/255.0f,104/255.0f,0.9f),
	};

	for (int i = 0; i < telopMax; i++)
	{
		bg[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2,SCREEN_HEIGHT / 10 * 2.0f +i* 240.0f),
			D3DXVECTOR2(1600.0f, 160.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/ScoreBG.png");
		bg[i]->SetColor(telopColor[i]);

		fieldText[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2, bg[i]->position.y-120.0f),
			D3DXVECTOR2(1024 / 2.0f, 1024 / 8.0f),"data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/FieldText.png");
		fieldText[i]->SetTexture(1, 4,i);

		scoreText[i] = new TextViewer("data/FONT/Makinas-4-Square.otf", 70);
		scoreText[i]->SetPos((int)(-SCREEN_WIDTH*2), (int)(bg[i]->position.y - 40.0f));

		rewardText[i] = new TextViewer("data/FONT/Makinas-4-Square.otf", 70);
		rewardText[i]->SetPos((int)(-SCREEN_WIDTH*2), (int)(bg[i]->position.y + 40.0f));
	}

	anim[AnimLayer::TelopIn] = new ViewerAnimater();
	anim[AnimLayer::TelopOut] = new ViewerAnimater();
	std::vector<std::function<void()>> inVec = {
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
	std::vector<std::function<void()>> outVec = {
		[=] {
		//�V�e�B�e���b�v�X�N���[���A�E�g
		OutCityTelop();
	},
		[=] {
		//���[���h�e���b�v�X�N���[���A�E�g
		OutWorldTelop();
	},
		[=] {
		//�X�y�[�X�e���b�v�X�N���[���A�E�g
		OutSpaceTelop();
	},
		[=] {
		//���U���g�e���b�v�X�N���[���A�E�g
		OutResultTelop();
	} };
	anim[AnimLayer::TelopIn]->SetAnimBehavior(inVec);
	anim[AnimLayer::TelopOut]->SetAnimBehavior(outVec);

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
	SAFE_DELETE(anim[AnimLayer::TelopIn]);
	SAFE_DELETE(anim[AnimLayer::TelopOut]);
}

//=============================================================================
// �X�V����
//=============================================================================
void ResultScoreViewer::Update(void)
{
	if (isInPlaying)
	{
		SetText();
		anim[AnimLayer::TelopIn]->PlayAnim([=]
		{
			anim[AnimLayer::TelopIn]->SetPlayFinished(isInPlaying, [=]
			{
				this->CallbackInFin();
			});
		});
	}
	if (isOutPlaying)
	{
		anim[AnimLayer::TelopOut]->PlayAnim([=]
		{
			anim[AnimLayer::TelopOut]->SetPlayFinished(isOutPlaying, [=]
			{
				//�Đ��I���̒ʒm
			});
		});
	}
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
// �e���b�v��~���W�擾����
//=============================================================================
void ResultScoreViewer::GetStopPos()
{
	for (int i = 0; i < telopMax; i++)
	{
		bgStopPos[i] = D3DXVECTOR2(bg[i]->position.x, bg[i]->position.y);
		fieldTextStopPos[i] = D3DXVECTOR2(fieldText[i]->position.x, fieldText[i]->position.y);
	}
}

//=============================================================================
// �e�L�X�g�\���Z�b�g����
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
	const float telopPosX = SCREEN_WIDTH / 15.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 1;

	anim[AnimLayer::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimLayer::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimLayer::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc,[=]
			{
				anim[AnimLayer::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
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
	const float telopPosX = SCREEN_WIDTH / 15.0f*2.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 2;

	anim[AnimLayer::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimLayer::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimLayer::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimLayer::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
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
	const float telopPosX = SCREEN_WIDTH / 15.0f*3.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 3;

	anim[AnimLayer::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimLayer::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimLayer::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimLayer::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
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
	const float telopPosX = SCREEN_WIDTH / 15.0f*4.0f;	
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 0;

	anim[AnimLayer::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimLayer::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX - fieldTelopGapPos*1.60f, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimLayer::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimLayer::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x-300.0f), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x-480.0f), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �V�e�B�e���b�v�X�N���[���A�E�g����
//=============================================================================
void ResultScoreViewer::OutCityTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 1;

	anim[AnimLayer::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCubic, [=]
	{
		anim[AnimLayer::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// ���[���h�e���b�v�X�N���[���A�E�g����
//=============================================================================
void ResultScoreViewer::OutWorldTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 2;

	anim[AnimLayer::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCubic, [=]
	{
		anim[AnimLayer::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �X�y�[�X�e���b�v�X�N���[���A�E�g����
//=============================================================================
void ResultScoreViewer::OutSpaceTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 3;

	anim[AnimLayer::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCubic, [=]
	{
		anim[AnimLayer::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// ���U���g�e���b�v�X�N���[���A�E�g����
//=============================================================================
void ResultScoreViewer::OutResultTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 0;

	anim[AnimLayer::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCubic, [=]
	{
		anim[AnimLayer::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX - fieldTelopGapPos * 1.5f, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x - 350.0f), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x - 370.0f), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::SetTelopIn(std::function<void()> CallbackInFin)
{
	this->CallbackInFin = CallbackInFin;
	isInPlaying = true;
}

//=============================================================================
// �e���b�v�X�N���[���A�E�g����
//=============================================================================
void ResultScoreViewer::SetTelopOut()
{
	GetStopPos();
	isOutPlaying = true;
}