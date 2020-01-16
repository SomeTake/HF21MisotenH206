//=============================================================================
//
// �`���[�g���A���r���[�A�N���X [TutorialViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "TutorialViewer.h"
#include "../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"

#include "../../../Framework/Core/Utility.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Input/input.h"

/**************************************
static�����o
***************************************/
const D3DXVECTOR3 DefaultTexturePos = D3DXVECTOR3(SCREEN_CENTER_X, 410.0f, 0.0f);
const char* TexturePath[TutorialViewer::HelpTextureType::Max] =
{
	"data/TEXTURE/Viewer/TutorialViewer/LinkRoad.png",
	"data/TEXTURE/Viewer/TutorialViewer/Develop.png",
	"data/TEXTURE/Viewer/TutorialViewer/ChangeCamera.png",
	"data/TEXTURE/Viewer/TutorialViewer/Event.png",
	"data/TEXTURE/Viewer/TutorialViewer/HighScore.png",
};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
TutorialViewer::TutorialViewer() :
	TextureNum(LinkRoad),
	IsShowTexture(false)
{
	// ��\������
	isPlaying = false;

	BackGround = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	BackGround->LoadTexture("data/TEXTURE/Viewer/TutorialViewer/BackGround.png");
	BackGround->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	BackGround->SetAlpha(0.5f);

	HelpTexture.reserve(HelpTextureType::Max);
	for (int i = 0; i < HelpTextureType::Max; i++)
	{
		HelpTexture.push_back(new TextureDrawer({ 1280.0f, 820.0f }));
		HelpTexture.at(i)->LoadTexture(TexturePath[i]);
		HelpTexture.at(i)->SetPosition(DefaultTexturePos);
	}

	MessageFrame = new TextureDrawer(D3DXVECTOR2(1280.0f, 250.0f));
	MessageFrame->LoadTexture("data/TEXTURE/Viewer/TutorialViewer/MessageFrame.png");
	MessageFrame->SetPosition({ SCREEN_CENTER_X, 950.0f, 0.0f });

	DescriptionText = new TextViewer("�}�L�i�X 4 Square", 50);;
	DescriptionText->SetPosition(D3DXVECTOR3(350.0f, 950.0f, 0.0f));
	DescriptionText->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);
	DescriptionText->SetText("�����͑�������ł��B");

	ExitText = new TextViewer("�}�L�i�X 4 Square", 80);;
	ExitText->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 950.0f, 0.0f));
	ExitText->SetText("");
	ExitText->SetActive(false);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
TutorialViewer::~TutorialViewer()
{
	SAFE_DELETE(BackGround);
	SAFE_DELETE(MessageFrame);
	SAFE_DELETE(DescriptionText);
	Utility::DeleteContainer(HelpTexture);
}

//=============================================================================
// ������
//=============================================================================
void TutorialViewer::Init(void)
{
	isPlaying = false;
	IsShowTexture = false;
	TextureNum = LinkRoad;
	BackGround->SetVisible(false);
	HelpTexture.at(TextureNum)->SetVisible(false);
	MessageFrame->SetVisible(false);
	DescriptionText->SetActive(false);
	ExitText->SetActive(false);
	ExitText->SetText("");
}

//=============================================================================
// �X�V����
//=============================================================================
void TutorialViewer::Update()
{
	if (!isPlaying)
		return;

	HelpTexture.at(TextureNum)->Update();

	/*
	static D3DXVECTOR3 FramePos = D3DXVECTOR3(SCREEN_CENTER_X, 925.0f, 0.0f);
	static D3DXVECTOR3 TextPos = D3DXVECTOR3(350.0f, 900.0f, 0.0f);
	Debug::Begin("TutorialLayout");
	Debug::Input("FramePos", FramePos);
	Debug::Input("TextPos", TextPos);
	MessageFrame->SetPosition(FramePos);
	DescriptionText->SetPosition(TextPos);
	Debug::End();
	*/
}

//=============================================================================
// �`�揈��
//=============================================================================
void TutorialViewer::Draw()
{
	if (!isPlaying)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// �����w�i
	BackGround->Draw();

	// �������
	HelpTexture.at(TextureNum)->Draw();

	// �e�L�X�g�̃t���[��
	MessageFrame->Draw();

	// �����e�L�X�g
	DescriptionText->Draw();

	// �I���e�L�X�g
	ExitText->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �`���[�g���A���̐�����ʂ�\��
//=============================================================================
void TutorialViewer::ShowTutorial(HelpTextureType Type)
{
	// �K�C�h���̉�ʂ��\��
	GuideViewer::Instance()->SetActive(false);

	// ������
	isPlaying = true;
	IsShowTexture = true;
	TextureNum = Type;
	BackGround->SetVisible(true);
	HelpTexture.at(TextureNum)->SetVisible(true);
	MessageFrame->SetVisible(true);
	DescriptionText->SetActive(true);
	ExitText->SetActive(false);

	// �摜�̃t�F�C�h�C��
	HelpTexture.at(TextureNum)->SetAlpha(0.0f);
	HelpTexture.at(TextureNum)->Fade(15.0f, 1.0f);

	// �����e�L�X�g�̐ݒu
	std::string text = "";
	switch (Type)
	{
	case TutorialViewer::LinkRoad:
		text += "�����m���q����悤�Ƀ��[�g�����ƁA�l���s�������Ĕ��W���܂��B\n";
		text += "���̒����ɐ����͂���܂��񂪁A\n";
		text += "�������Ƃ��͒����m���q�����Ă���K�v������܂��B";
		DescriptionText->SetText(text);
		ExitText->SetText("���𓹂Ōq��");
		break;

	case TutorialViewer::Develop:
		text += "���R�Ȃǂ��w�肵�ă��[�g�����ƁA\n";
		text += "�J�񂵂ē���u����悤�ɂȂ�܂��B\n";
		text += "�J��1�}�X�ɂ��A��ʍ��̃X�g�b�N��1�g���܂��B\n";
		DescriptionText->SetText(text);
		ExitText->SetText("�t�B�[���h���J�񂷂�");
		break;

	case TutorialViewer::ChangeCamera:
		text += "�J�����𓮂����Ď��_��؂�ւ��邱�Ƃ��ł��܂��B\n";
		text += "�t�B�[���h���������璭�߂ĊJ���v��𗧂Ă܂��傤�B\n";
		text += "�������璭�߂Ă�Ԃ̓��[�g����邱�Ƃ��ł��܂���B";
		DescriptionText->SetText(text);
		ExitText->SetText("�J������؂�ւ���");
		break;

	case TutorialViewer::EventHappend:
		text += "�����o�Ă���}�X�ɓ���u���Ɨl�X�ȃC�x���g���������܂��B\n";
		text += "�v���C���[�ɂƂ��ėǂ��C�x���g�����łȂ��A\n";
		text += "�����C�x���g���N���邱�Ƃ�����̂Œ��ӂ��܂��傤�B";
		DescriptionText->SetText(text);
		ExitText->SetText("���ŃC�x���g�}�X�𕢂�");
		break;

	case TutorialViewer::HighScore:
		text += "��x�ɂ�������̒����q������悤�ɓ����q���ƁA\n";
		text += "��������̃|�C���g������A�X�R�A�������Ȃ�܂��B\n";
		text += "�n�C�X�R�A��ڎw���Ċ撣��܂��傤�B\n";
		DescriptionText->SetText(text);
		if (GamePad::GetPadCount() == 0)
		{
			ExitText->SetText("�`���[�g���A���I���FEnter Key");
		}
		else
		{
			ExitText->SetText("�`���[�g���A���I���FOption Button");
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// �w���v�e�L�X�g��\��
//=============================================================================
void TutorialViewer::SetHelpMessage(void)
{
	isPlaying = true;
	BackGround->SetVisible(false);
	HelpTexture.at(TextureNum)->SetVisible(false);
	MessageFrame->SetVisible(false);
	DescriptionText->SetActive(false);
	ExitText->SetActive(true);
}
