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
static const D3DXVECTOR2 scoreTextGapPos = D3DXVECTOR2(-60.0f,-40.0f);
static const D3DXVECTOR2 rewardTextGapPos = D3DXVECTOR2(60.0f, 35.0f);
static const float fieldTelopGapPos = 200.0f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ResultScoreViewer::ResultScoreViewer() :
	parameterBoxScore(),
	parameterBoxRoad(),
	parameterBoxCity(),
	score(),
	connectedCity(),
	builtRoad(),
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
			D3DXVECTOR2(1700.0f, 160.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/ScoreBG.png");
		bg[i]->SetColor(telopColor[i]);

		fieldText[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2, bg[i]->position.y-120.0f),
			D3DXVECTOR2(1024 / 2.0f, 1024 / 8.0f),"data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/FieldText.png");
		fieldText[i]->SetTexture(1, 4,i);

		scoreText[i] = new TextViewer("�}�L�i�X 4 Square", 70);
		scoreText[i]->SetPos((int)(-SCREEN_WIDTH*2), (int)(bg[i]->position.y - 40.0f));

		rewardText[i] = new TextViewer("�}�L�i�X 4 Square", 70);
		rewardText[i]->SetPos((int)(-SCREEN_WIDTH*2), (int)(bg[i]->position.y + 40.0f));
	}

	anim[AnimType::TelopIn] = new ViewerAnimater();
	anim[AnimType::TelopOut] = new ViewerAnimater();
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
	anim[AnimType::TelopIn]->SetAnimBehavior(inVec);
	anim[AnimType::TelopOut]->SetAnimBehavior(outVec);

	//�p�����[�^�Z�b�g
	SetRecievedParam();
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
	SAFE_DELETE(anim[AnimType::TelopIn]);
	SAFE_DELETE(anim[AnimType::TelopOut]);
}

//=============================================================================
// �X�V����
//=============================================================================
void ResultScoreViewer::Update(void)
{
	SetText();
	if (isInPlaying)
	{
		anim[AnimType::TelopIn]->PlayAnim([=]
		{
			anim[AnimType::TelopIn]->SetPlayFinished(isInPlaying, [=]
			{
				if(this->CallbackInFin != nullptr)
					this->CallbackInFin();
			});
		});
	}
	if (isOutPlaying)
	{
		anim[AnimType::TelopOut]->PlayAnim([=]
		{
			anim[AnimType::TelopOut]->SetPlayFinished(isOutPlaying, [=]
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
// �e�L�X�g�\���Z�b�g����
//=============================================================================
void ResultScoreViewer::SetText()
{
	//�����ŃX�R�A��\���ł���悤�ɂ���
	for (int i = 0; i < telopMax; i++)
	{
		rewardText[i]->SetText("��������̐��F10�@�q�������X�̐��F10");
	}
	scoreText[0]->SetText("9999��9999��9999��9999");
	scoreText[1]->SetText("�X�R�A�F9999");
	scoreText[2]->SetText("�X�R�A�F9999��");
	scoreText[3]->SetText("�X�R�A�F9999��");
}

//=============================================================================
// �󂯎�����p�����[�^���Z�b�g���鏈��
//=============================================================================
void ResultScoreViewer::SetRecievedParam()
{
	//�X�R�A
	score[City] = parameterBoxScore[City];
	score[World] = parameterBoxScore[World];
	score[Space] = parameterBoxScore[Space] % 99990000;
	score[Risult] = (int)parameterBoxScore[2] / 10000;//�X�R�A�͕����ĕ\������̂ŕʁX�Ƀp�����[�^���i�[

	//�������
	builtRoad[City] = parameterBoxRoad[City];
	builtRoad[World] = parameterBoxRoad[World];
	builtRoad[Space] = parameterBoxRoad[Space];
	builtRoad[Risult] = parameterBoxRoad[City] + parameterBoxRoad[World] + parameterBoxRoad[Space];

	//�q�������X
	connectedCity[City] = parameterBoxCity[City];
	connectedCity[World] = parameterBoxCity[World];
	connectedCity[Space] = parameterBoxCity[Space];
	connectedCity[Risult] = parameterBoxCity[City] + parameterBoxCity[World] + parameterBoxCity[Space];
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
// �V�e�B�e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::InCityTelop()
{
	const float telopPosX = SCREEN_WIDTH / 15.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 1;

	anim[AnimType::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimType::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimType::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc,[=]
			{
				anim[AnimType::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// ���[���h�e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::InWorldTelop()
{
	const float telopPosX = SCREEN_WIDTH / 15.0f*2.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 2;

	anim[AnimType::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimType::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimType::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimType::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});
		}
		);
	});

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x-34.0f), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �X�y�[�X�e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::InSpaceTelop()
{
	const float telopPosX = SCREEN_WIDTH / 15.0f*3.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 3;

	anim[AnimType::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimType::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimType::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimType::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x - 34.0f), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// ���U���g�e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::InResultTelop()
{
	const float telopPosX = SCREEN_WIDTH / 15.0f*4.0f;	
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 0;

	anim[AnimType::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimType::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX - fieldTelopGapPos*1.70f, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimType::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimType::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//�J�E���g�A�b�v����
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x+290.0f), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x+100.0f), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �V�e�B�e���b�v�X�N���[���A�E�g����
//=============================================================================
void ResultScoreViewer::OutCityTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 1;

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCubic, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
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

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCubic, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
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

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCubic, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
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

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCubic, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX - fieldTelopGapPos * 1.5f, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x + 350.0f), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x - 370.0f), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �e���b�v�X�N���[���C������
//=============================================================================
void ResultScoreViewer::SetTelopIn(std::function<void()> CallbackInFin)
{
	this->CallbackInFin = CallbackInFin;
	isInPlaying = true;
	anim[AnimType::TelopIn]->ResetAnim();
}

//=============================================================================
// �e���b�v�X�N���[���A�E�g����
//=============================================================================
void ResultScoreViewer::SetTelopOut()
{
	GetStopPos();
	isOutPlaying = true;
	anim[AnimType::TelopOut]->ResetAnim();
}

//=============================================================================
// �e���b�v�X�N���[���C���Đ�������
//=============================================================================
bool ResultScoreViewer::IsPlayingIn() const
{
	return isInPlaying;
}

//=============================================================================
// �e���b�v�X�N���[���A�E�g�Đ�������
//=============================================================================
bool ResultScoreViewer::IsPlayingOut() const
{
	return isOutPlaying;
}
