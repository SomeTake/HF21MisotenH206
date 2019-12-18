//=====================================
//
//ResultAchieveViewer.cpp
//�@�\:���U���g��ʂ̎��уr���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResultAchieveViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../../../Framework/Tween/Tween.h"
#include "../../../../Framework/Tool/DebugWindow.h"

/**************************************
static�����o
***************************************/
const D3DXVECTOR3 ResultAchieveViewer::InitTitlePos = { -200.0f, 80.0f, 0.0f };
const D3DXVECTOR3 ResultAchieveViewer::DestTitlePos = { 200.0f, 80.0f, 0.0f };
const int ResultAchieveViewer::SizeTextFont = 90;
const D3DXVECTOR3 ResultAchieveViewer::InitTextPos = { -ResultAchieveViewer::SizeTextFont * 13, 200.0f, 0.0f };

/**************************************
�R���X�g���N�^
***************************************/
ResultAchieveViewer::ResultAchieveViewer()
{
	// ��\������
	isPlaying = false;

	const D3DXVECTOR2 SizeBG = { 1200.0f, SizeTextFont * 10.5f };
	bg = new TextureDrawer(SizeBG, false);
	bg->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/scoreBG.png");
	bg->SetPosition({ SizeBG.x / 2.0f, InitTextPos.y + SizeTextFont * 4.5f, 0.0f });
	bg->SetColor(D3DXCOLOR(0.0f, 104 / 255.0f, 98 / 255.0f, 0.9f));

	title = new TextureDrawer({ 300.0f, 150.0f });
	title->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultAchieveViewer/AchieveTitle.png");
	title->SetPosition(InitTitlePos);

	NewIcon = new TextureDrawer(D3DXVECTOR2(250.0f, 50.0f));
	NewIcon->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultAchieveViewer/NewAchieve.png");
	NewIcon->SetPosition(D3DXVECTOR3(80.0f, 160.0f, 0.0f));

	textContainer.resize(RewardConfig::Type::Max, nullptr);
	for (unsigned i = 0; i < textContainer.size(); i++)
	{
		TextViewer *text = new TextViewer("�}�L�i�X 4 Square", SizeTextFont);;
		text->SetActive(false);

		D3DXVECTOR3 textPos = InitTextPos + Vector3::Up * (float)SizeTextFont * (float)i;
		text->SetPosition(textPos);

		text->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);

		textContainer[i] = text;
	}
}

/**************************************
�f�X�g���N�^
***************************************/
ResultAchieveViewer::~ResultAchieveViewer()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(title);
	SAFE_DELETE(NewIcon);

	for (auto&& text : textContainer)
	{
		SAFE_DELETE(text);
	}
	textContainer.clear();
}

/**************************************
�X�V����
***************************************/
void ResultAchieveViewer::Update()
{
	if (!isPlaying)
		return;

#if _DEBUG
	Debug::Begin("TexturePos");
	static D3DXVECTOR3 IconPos = D3DXVECTOR3(80.0f, 160.0f, 0.0f);
	Debug::Input("IconPos", IconPos);
	NewIcon->SetPosition(IconPos);
	Debug::End();
#endif

	bg->Update();
	title->Update();
}

/**************************************
�`�揈��
***************************************/
void ResultAchieveViewer::Draw()
{
	if (!isPlaying)
		return;

	bg->Draw();
	title->Draw();

	for (auto&& text : textContainer)
	{
		text->Draw();
	}

	NewIcon->Draw();
}

/**************************************
�B���������т�ݒ�
***************************************/
void ResultAchieveViewer::SetReward(std::vector<RewardConfig::Type>& rewardContainer)
{
	using RewardConfig::RewardName;

	//�B�����Ă�����і����e�L�X�g�r���[���ɐݒ�
	for (unsigned i = 0; i < textContainer.size(); i++)
	{
		TextViewer *text = textContainer[i];

		std::string rewardName = i < rewardContainer.size() ? RewardName[rewardContainer[i]] : "";
		text->SetText(rewardName);
	}
}

/**************************************
�A�j���[�V�����J�n
***************************************/
void ResultAchieveViewer::StartAnim(std::function<void()> callback)
{
	//�e�L�X�g����U�S�Ĕ�\��
	for (auto&& text : textContainer)
	{
		text->SetActive(false);
	}

	//�^�C�g���̈ʒu��������
	title->SetPosition(InitTitlePos);

	//�A�j���[�V�����J�n
	bg->Expand(30, ExpandType::LeftToRight, EaseType::OutCubic);
	title->Move(30, DestTitlePos, EaseType::OutCubic, [this, callback]()
	{
		SlideinText();
		callback();
	});
}

/**************************************
�e�L�X�g�̃X���C�h�C��
***************************************/
void ResultAchieveViewer::SlideinText()
{
	D3DXVECTOR3 initPos = InitTextPos;
	D3DXVECTOR3 destPos = { 50.0f, initPos.y, 0.0f };
	int delay = 2;

	for (auto&& text : textContainer)
	{
		if (text->GetText() == "")
			continue;

		text->SetPosition(initPos);
		text->SetActive(true);

		TaskManager::Instance()->CreateDelayedTask(delay, [&, text, initPos, destPos]()
		{
			Tween::Move(*text, destPos, 30, EaseType::OutCubic);
		});

		initPos.y += (float)SizeTextFont;
		destPos.y += (float)SizeTextFont;
		delay += 5;
	}
}
