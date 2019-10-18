//=============================================================================
//
// イベントコントローラークラス [EventController.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "EventController.h"
#include "EventConfig.h"
#include "PlusEvent/AILevelUpEvent.h"
#include "PlusEvent/BonusEvent.h"
#include "PlusEvent/CityLevelUpEvent.h"
#include "PlusEvent/FamousPeopleEvent.h"
#include "PlusEvent/NewCityEvent.h"
#include "PlusEvent/StockRecoveryEvent.h"
#include "MinusEvent/AILevelDecreaseEvent.h"
#include "MinusEvent/BanStockUseEvent.h"
#include "MinusEvent/CityDestroyEvent.h"
#include "MinusEvent/CityLevelDecreaseEvent.h"
#include "MinusEvent/CongestionUpEvent.h"
#include "MinusEvent/MoveInverseEvent.h"

#include "../../Framework/Core/Utility.h"
#include "../../Framework/String/String.h"

#include <fstream>

#if _DEBUG
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"
#endif

using namespace EventConfig;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 使用していないイベントを削除
bool RemoveCondition(EventBase *Event) { return Event == nullptr ? true : false; }

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
EventController::EventController(int FieldLevel) : FieldLevel(FieldLevel)
{
	LoadCSV("data/FIELD/sample01_Event.csv");

	eventViewer = new EventViewer();

#if _DEBUG
	ResourceManager::Instance()->MakePolygon("Event", "data/TEXTURE/PlaceTest/Event.png", { 4.5f, 4.5f }, { 12.0f,1.0f });
#endif
}

//=============================================================================
// デストラクタ
//=============================================================================
EventController::~EventController()
{
	// イベントベクトル削除
	Utility::DeleteContainer(EventVec);
	EventCSVData.clear();

	fieldController = nullptr;

	SAFE_DELETE(eventViewer);
}

//=============================================================================
// 更新
//=============================================================================
void EventController::Update()
{
	for (auto &Event : EventVec)
	{
		if (Event->GetUse())
		{
			Event->Update();
		}
		else
		{
			// 使用完了のイベントを削除
			SAFE_DELETE(Event);
		}
	}

	// イベントビューア更新
	eventViewer->Update();

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), RemoveCondition), std::end(EventVec));
}

//=============================================================================
// 描画
//=============================================================================
void EventController::Draw()
{
	for (auto &Event : EventVec)
	{
		Event->Draw();
	}

	// イベントビューア描画
	eventViewer->Draw();

#if _DEBUG
	// イベントマスの可視化描画
	DrawDebug();
#endif
}

#if _DEBUG
//=============================================================================
// イベントマスの可視化描画
//=============================================================================
void EventController::DrawDebug()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (auto& Object : EventCSVData)
	{
		//テスト描画
		Transform transform = Transform(
			Object.Pos.ConvertToWorldPosition() + D3DXVECTOR3(0.0f, 1.0f, 0.0f),
			{ D3DXToRadian(90.0f), 0.0f, 0.0f },
			Vector3::One);
		transform.SetWorld();
		BoardPolygon *polygon;
		ResourceManager::Instance()->GetPolygon("Event", polygon);
		polygon->SetTextureIndex(Object.EventType);
		polygon->Draw();
	}

	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
#endif

//=============================================================================
// CSVの読み込む
//=============================================================================
void EventController::LoadCSV(const char* FilePath)
{
	//初期化済みであればリターン
	//if (initialized)
	//	return;

	//CSVファイルを読み込み
	std::ifstream stream(FilePath);

	std::string line;			// CSVを1行ずつ読むバッファ
	const char Delim = ',';		// 区切り文字
	int x = 0;					// EventのX位置
	int z = 0;					// EventのZ位置

	//CSVの終わりまで読み込み続ける
	while (std::getline(stream, line))
	{
		//1行分読み込んだデータを区切り文字で分割する
		std::vector<std::string> subStr;
		String::Split(subStr, line, Delim);

		x = 0;

		for (auto &str : subStr)
		{
			int Type = std::stoi(str);
			if (Type != EventConfig::NoEvent)
			{
				Field::FieldPosition Pos = { x, z };
				EventCSVData.push_back(EventInfo{ Pos, Type });
			}
			x++;
		}
		z++;
	}

	//初期化完了
	//initialized = true;
}

//=============================================================================
// イベント発生の確認
//=============================================================================
void EventController::CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& RoutePtr, int FieldLevel)
{
	for (auto &place : RoutePtr)
	{
		Field::FieldPosition PlacePos = place->GetPosition();
		for (auto EventPlace = EventCSVData.begin(); EventPlace != EventCSVData.end();)
		{
			if (PlacePos.x == EventPlace->Pos.x && PlacePos.z == EventPlace->Pos.z)
			{
				EventBase* Ptr = nullptr;

				// イベントインスタンス作成
				switch (EventPlace->EventType)
				{
				case CityLevelUp:
					Ptr = new CityLevelUpEvent();
					break;
				case NewCity:
					Ptr = new NewCityEvent();
					break;
				case StockRecovery:
					Ptr = new StockRecoveryEvent();
					break;
				case FamousPeople:
					//Ptr = new FamousPeopleEvent();
					break;
				case Bonus:
					Ptr = new BonusEvent();
					break;
				case AILevelUp:
					Ptr = new AILevelUpEvent();
					break;
				case CityLevelDecrease:
					Ptr = new CityLevelDecreaseEvent();
					break;
				case CityDestroy:
					Ptr = new CityDestroyEvent(D3DXVECTOR3(150.0f, 0.0f, -150.0f));
					break;
				case AILevelDecrease:
					Ptr = new AILevelDecreaseEvent();
					break;
				case MoveInverse:
					//Ptr = new MoveInverseEvent();
					break;
				case BanStockUse:
					//Ptr = new BanStockUseEvent();
					break;
				case CongestionUp:
					//Ptr = new CongestionUpEvent();
					break;
				default:
					break;
				}
				if (Ptr != nullptr)
				{
				// イベントメッセージ設置
				eventViewer->SetEventMessage(Ptr->GetEventMessage(FieldLevel));

				// イベントベクトルにプッシュ
				EventVec.push_back(Ptr);
          
				// CSVデータから発生したイベントの資料を削除
				EventPlace = EventCSVData.erase(EventPlace);
				}
			}
			else
				++EventPlace;
		}
	}
}

//=============================================================================
// FieldControllerのポインタを受け取る
//=============================================================================
void EventController::ReceiveFieldController(Field::FieldController *Ptr)
{
	EventBase::ReceiveFieldController(Ptr);
}