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

using std::to_string;
using std::string;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static const D3DXVECTOR2 scoreTextGapPos = D3DXVECTOR2(-120.0f,-40.0f);
static const D3DXVECTOR2 rewardTextGapPos = D3DXVECTOR2(-120.0f, 35.0f);
static const float fieldTelopGapPos = 200.0f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ResultScoreViewer::ResultScoreViewer() :
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
		bg[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2,SCREEN_HEIGHT / 10 * 1.70f +i* 250.0f),
			D3DXVECTOR2(1700.0f, 160.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/ScoreBG.png");
		bg[i]->SetColor(telopColor[i]);

		fieldText[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2, bg[i]->position.y-120.0f),
			D3DXVECTOR2(1024 / 2.0f, 1024 / 8.0f),"data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/FieldText.png");
		fieldText[i]->SetTexture(1, 4,i);

		scoreText[i] = new TextViewer("�}�L�i�X 4 Square", 80);
		scoreText[i]->SetPos((int)(-SCREEN_WIDTH*2), (int)(bg[i]->position.y - 40.0f));
		scoreText[i]->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);

		rewardText[i] = new TextViewer("�}�L�i�X 4 Square", 40);
		rewardText[i]->SetPos((int)(-SCREEN_WIDTH*2), (int)(bg[i]->position.y + 40.0f));
		rewardText[i]->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);
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
// �󂯎�����p�����[�^���Z�b�g���鏈��
//=============================================================================
void ResultScoreViewer::ReceiveParam(const ResultViewerParam& ResultPara)
{
	string BuildRoad;
	string ConnectedCity;

	//�����ŃX�R�A��\���ł���悤�ɂ���
	// scoreText[0] = Total Result
	// scoreText[1] = City
	// scoreText[2] = World
	// scoreText[3] = Spcae

	// City Level
	scoreText[1]->SetText("�X�R�A�F" + to_string(ResultPara.score[City]));
	BuildRoad = "��������̐��@�F" + to_string(ResultPara.builtRoad[City]);
	ConnectedCity = "�q�������X�̐��F" + to_string(ResultPara.connectedCity[City]);
	rewardText[1]->SetText(BuildRoad + "\n" + ConnectedCity);

	// World Level
	scoreText[2]->SetText("�X�R�A�F" + to_string(ResultPara.score[World]) + "��");
	BuildRoad = "��������̐��@�F" + to_string(ResultPara.builtRoad[World]);
	ConnectedCity = "�q�������X�̐��F" + to_string(ResultPara.connectedCity[World]);
	rewardText[2]->SetText(BuildRoad + "\n" + ConnectedCity);

	// Space Level
	// ��
	int BillionNum = ResultPara.score[Space] % 10000;
	// ��
	int TrillionNum = ResultPara.score[Space] / 10000;
	if (ResultPara.score[Space] <= 9999)
	{
		scoreText[3]->SetText("�X�R�A�F" + to_string(ResultPara.score[Space]) + "��");
	}
	else
	{
		scoreText[3]->SetText("�X�R�A�F" + to_string(TrillionNum) + "��" + to_string(BillionNum) + "��");
	}
	BuildRoad = "��������̐��@�F" + to_string(ResultPara.builtRoad[Space]);
	ConnectedCity = "�q�������X�̐��F" + to_string(ResultPara.connectedCity[Space]);
	rewardText[3]->SetText(BuildRoad + "\n" + ConnectedCity);

	// Total Result

	if (ResultPara.score[Space] > 9999)
	{
		string TotalScoreStr = 
			to_string(TrillionNum) + "��" +
			to_string(BillionNum) + "��" +
			to_string(ResultPara.score[World]) + "��" +
			to_string(ResultPara.score[City]);
		scoreText[0]->SetText("���v�X�R�A�F" + TotalScoreStr);
	}
	else if (ResultPara.score[Space] > 0 && ResultPara.score[Space] < 9999)
	{
		string TotalScoreStr = 
			to_string(ResultPara.score[Space]) + "��" +
			to_string(ResultPara.score[World]) + "��" +
			to_string(ResultPara.score[City]);
		scoreText[0]->SetText("���v�X�R�A�F" + TotalScoreStr);
	}
	else if (ResultPara.score[Space] == 0 && ResultPara.score[World] != 0)
	{
		string TotalScoreStr =
			to_string(ResultPara.score[World]) + "��" +
			to_string(ResultPara.score[City]);
		scoreText[0]->SetText("���v�X�R�A�F" + TotalScoreStr);
	}
	else if (ResultPara.score[World] == 0 && ResultPara.score[City] != 0)
	{
		string TotalScoreStr = to_string(ResultPara.score[City]);
		scoreText[0]->SetText("���v�X�R�A�F" + TotalScoreStr);
	}
	else if (ResultPara.score[City] == 0)
	{
		scoreText[0]->SetText("���v�X�R�A�F0");
	}
	int TotalRoadNum = ResultPara.builtRoad[City] + ResultPara.builtRoad[World] + ResultPara.builtRoad[Space];
	int TotalCityNum = ResultPara.connectedCity[City] + ResultPara.connectedCity[World] + ResultPara.connectedCity[Space];
	BuildRoad = "��������̐��@�F" + to_string(TotalRoadNum);
	ConnectedCity = "�q�������X�̐��F" + to_string(TotalCityNum);
	rewardText[0]->SetText(BuildRoad + "\n" + ConnectedCity);
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
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
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
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
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

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// �V�e�B�e���b�v�X�N���[���A�E�g����
//=============================================================================
void ResultScoreViewer::OutCityTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 1;

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCirc, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX/4 + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
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

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCirc, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX / 4 + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
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

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCirc, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX / 4 + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
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

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCirc, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX/4 + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
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