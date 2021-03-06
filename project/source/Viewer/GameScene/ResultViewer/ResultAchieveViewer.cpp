//=====================================
//
//ResultAchieveViewer.cpp
//機能:リザルト画面の実績ビューワ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResultAchieveViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../../../Framework/Tween/Tween.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../Reward/RewardController.h"

/**************************************
staticメンバ
***************************************/
const D3DXVECTOR3 ResultAchieveViewer::InitTitlePos = { -200.0f, 80.0f, 0.0f };
const D3DXVECTOR3 ResultAchieveViewer::DestTitlePos = { 200.0f, 80.0f, 0.0f };
const int ResultAchieveViewer::SizeTextFont = 90;
const D3DXVECTOR3 ResultAchieveViewer::InitTextPos = { -ResultAchieveViewer::SizeTextFont * 13, 200.0f, 0.0f };
//const D3DXVECTOR3 ResultAchieveViewer::InitIconPos = D3DXVECTOR3(80.0f, 160.0f, 0.0f);
const D3DXVECTOR3 ResultAchieveViewer::InitIconPos = D3DXVECTOR3(-1140.0f, 160.0f, 0.0f);

/**************************************
コンストラクタ
***************************************/
ResultAchieveViewer::ResultAchieveViewer()
{
	// 非表示する
	isPlaying = false;

	const D3DXVECTOR2 SizeBG = { 1200.0f, SizeTextFont * 10.5f };
	bg = new TextureDrawer(SizeBG, false);
	bg->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/scoreBG.png");
	bg->SetPosition({ SizeBG.x / 2.0f, InitTextPos.y + SizeTextFont * 4.5f, 0.0f });
	bg->SetColor(D3DXCOLOR(0.0f, 104 / 255.0f, 98 / 255.0f, 0.9f));

	title = new TextureDrawer({ 300.0f, 150.0f });
	title->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultAchieveViewer/AchieveTitle.png");
	title->SetPosition(InitTitlePos);

	NewIconContainer.reserve(RewardConfig::Type::Max);
	for (unsigned i = 0; i < RewardConfig::Type::Max; i++)
	{
		NewIconContainer.push_back(new TextureDrawer(D3DXVECTOR2(250.0f, 50.0f), false));
		NewIconContainer.at(i)->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultAchieveViewer/NewAchieve.png");

		D3DXVECTOR3 IconPos = InitIconPos + Vector3::Up * (float)SizeTextFont * (float)i;
		NewIconContainer.at(i)->SetPosition(IconPos);
	}

	textContainer.resize(RewardConfig::Type::Max, nullptr);
	for (unsigned i = 0; i < textContainer.size(); i++)
	{
		TextViewer *text = new TextViewer("マキナス 4 Square", SizeTextFont);;
		text->SetActive(false);

		D3DXVECTOR3 textPos = InitTextPos + Vector3::Up * (float)SizeTextFont * (float)i;
		text->SetPosition(textPos);

		text->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);

		textContainer[i] = text;
	}
}

/**************************************
デストラクタ
***************************************/
ResultAchieveViewer::~ResultAchieveViewer()
{
	SAFE_DELETE(bg);
	SAFE_DELETE(title);
	Utility::DeleteContainer(NewIconContainer);

	for (auto&& text : textContainer)
	{
		SAFE_DELETE(text);
	}
	textContainer.clear();
}

/**************************************
更新処理
***************************************/
void ResultAchieveViewer::Update()
{
	if (!isPlaying)
		return;

	bg->Update();
	title->Update();

	for (auto &Icon : NewIconContainer)
	{
		Icon->Update();
	}
}

/**************************************
描画処理
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

	for (auto &Icon : NewIconContainer)
	{
		Icon->Draw();
	}
}

/**************************************
達成した実績を設定
***************************************/
void ResultAchieveViewer::SetReward(std::vector<RewardConfig::Type>& rewardContainer)
{
	using RewardConfig::RewardName;

	//達成している実績名をテキストビューワに設定
	for (unsigned i = 0; i < textContainer.size(); i++)
	{
		TextViewer *text = textContainer[i];

		std::string rewardName = i < rewardContainer.size() ? RewardName[rewardContainer.at(i)] : "";
		text->SetText(rewardName);

		// この実績は初達成であれば、Newアイコンを付ける
		if (rewardName != "" && RewardController::Instance()->IsFirstAchieved(rewardContainer.at(i)) == false)
		{
			D3DXVECTOR3 IconPos = InitIconPos + Vector3::Up * (float)SizeTextFont * (float)i;
			NewIconContainer.at(i)->SetVisible(true);
			NewIconContainer.at(i)->SetPosition(IconPos);
		}
		else
		{
			NewIconContainer.at(i)->SetVisible(false);
		}
	}
}

/**************************************
アニメーション開始
***************************************/
void ResultAchieveViewer::StartAnim(std::function<void()> callback)
{
	//テキストを一旦全て非表示
	for (auto&& text : textContainer)
	{
		text->SetActive(false);
	}

	//タイトルの位置を初期化
	title->SetPosition(InitTitlePos);

	//アニメーション開始
	bg->Expand(30, ExpandType::LeftToRight, EaseType::OutCubic);
	title->Move(30, DestTitlePos, EaseType::OutCubic, [this, callback]()
	{
		SlideinText();
		callback();
	});
}

/**************************************
テキストのスライドイン
***************************************/
void ResultAchieveViewer::SlideinText()
{
	D3DXVECTOR3 initPos = InitTextPos;
	D3DXVECTOR3 destPos = { 50.0f, initPos.y, 0.0f };
	int delay = 2;

	// テキスト
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

	// Newアイコン
	delay = 2;
	for (auto & Icon : NewIconContainer)
	{
		D3DXVECTOR3 DestPos = Icon->GetPosition();
		DestPos.x = 80.0f;

		TaskManager::Instance()->CreateDelayedTask(delay, [&, DestPos]()
		{
			Icon->Move(30.0f, DestPos, EaseType::OutCubic);
		});

		delay += 5;
	}
}
