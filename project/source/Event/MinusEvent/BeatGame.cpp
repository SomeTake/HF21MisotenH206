//=============================================================================
//
// �A�ŃQ�[���C�x���g�N���X [BeatGame.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "BeatGame.h"
#include "../../Viewer/Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Viewer/Framework/ViewerDrawer/countviewerdrawer.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Input/input.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �A�ŃQ�[���̎���
const int InputTime = 3;
// �A�ł̉�
const int InputGoal = 20;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
TextViewer *BeatGame::Text = nullptr;
BaseViewerDrawer *BeatGame::point = nullptr;
CountViewerDrawer *BeatGame::fewNum = nullptr;
CountViewerDrawer *BeatGame::intNum = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
BeatGame::BeatGame(std::function<void(bool)> Callback) :
	RemainFrame(InputTime * 30),
	TelopOver(false),
	InputCount(0),
	Callback(Callback)
{
	Text->SetText("C�{�^���A�ŁI�@�c�� 20 ��");
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
BeatGame::~BeatGame()
{

}

//=============================================================================
// ������
//=============================================================================
void BeatGame::Init()
{
	// �e�L�X�g
	Text = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf", 80);
	Text->SetColor(SET_COLOR_NOT_COLORED);
	Text->SetPos((int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 10 * 2.0f + 120.0f));

	// ������
	intNum = new CountViewerDrawer();
	intNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	intNum->MakeVertex();
	intNum->size = D3DXVECTOR3(60.0f, 60.0f, 0.0f);
	intNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	intNum->position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 140.0f, SCREEN_HEIGHT / 10 * 2.0f + 20.0f, 0.0f);
	intNum->SetColor(SET_COLOR_NOT_COLORED);
	intNum->intervalNumberScr = 80.0f;
	intNum->intervalNumberTex = 0.1f;
	intNum->placeMax = 2;
	intNum->baseNumber = 10;

	// ������
	fewNum = new CountViewerDrawer();
	fewNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	fewNum->MakeVertex();
	fewNum->size = D3DXVECTOR3(30.0f, 30.0f, 0.0f);
	fewNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fewNum->position = D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, SCREEN_HEIGHT / 10 * 2.0f + 30.0f, 0.0f);
	fewNum->SetColor(SET_COLOR_NOT_COLORED);
	fewNum->intervalNumberScr = 40.0f;
	fewNum->intervalNumberTex = 0.1f;
	fewNum->placeMax = 2;
	fewNum->baseNumber = 10;

	// �����_
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Point.png");
	point->MakeVertex();
	point->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10 * 2.0f, 0.0f);
	point->SetColor(SET_COLOR_NOT_COLORED);
}

//=============================================================================
// �����[�X
//=============================================================================
void BeatGame::Uninit()
{
	SAFE_DELETE(Text);
	SAFE_DELETE(point);
	SAFE_DELETE(fewNum);
	SAFE_DELETE(intNum);
}

//=============================================================================
// �X�V
//=============================================================================
void BeatGame::Update()
{
	if (!UseFlag)
		return;

	if (!TelopOver)
	{
		return;
	}
	else
	{
		RemainFrame--;

		// �J�E���g�v�Z
		if (Keyboard::GetTrigger(DIK_C))
		{
			InputCount++;
		}

		char Message[64];
		sprintf(Message, "C�{�^���A�ŁI�@�c�� %d ��", InputGoal - InputCount);
		Text->SetText(Message);

		if (InputCount >= 20)
		{
			// ����
			Callback(true);
			UseFlag = false;
			return;
		}

		if (RemainFrame <= 0)
		{
			// ���s
			Callback(false);
			UseFlag = false;
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void BeatGame::Draw()
{
	if (!UseFlag)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �e�L�X�g
	Text->Draw();

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Device->SetRenderState(D3DRS_ALPHAREF, 0);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// �����_
	point->Draw();
	point->SetVertex();

	float RemainTime = RemainFrame / 30.0f;

	// ������
	intNum->DrawCounter(intNum->baseNumber, (int)RemainTime, intNum->placeMax,
		intNum->intervalNumberScr, intNum->intervalNumberTex);

	// ������
	fewNum->DrawCounter(fewNum->baseNumber, (int)((RemainTime - (int)RemainTime)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
		fewNum->intervalNumberScr, fewNum->intervalNumberTex);

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string BeatGame::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
void BeatGame::CountdownStart(void)
{
	TelopOver = true;
}