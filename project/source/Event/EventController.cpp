//=============================================================================
//
// �C�x���g�R���g���[���[�N���X [EventController.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "EventController.h"
#include "EventConfig.h"
#include "PlusEvent/AILevelUpEvent.h"
#include "PlusEvent/AllLinkLevelUpEvent.h"
#include "PlusEvent/TimeRecoveryEvent.h"
#include "PlusEvent/LinkLevelUpEvent.h"
#include "PlusEvent/FamousPeopleEvent.h"
#include "PlusEvent/CreateNewTown/NewTownEventCtrl.h"
#include "PlusEvent/StockRecoveryEvent.h"
#include "MinusEvent/AILevelDecreaseEvent.h"
#include "MinusEvent/BanStockUseEvent.h"
#include "MinusEvent/CityDestroyEvent.h"
#include "MinusEvent/LinkLevelDecreaseEvent.h"
#include "MinusEvent/BeatGame.h"

#include "../../Framework/Core/Utility.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../Framework/Camera/CameraShakePlugin.h"

#include "../Field/Place/FieldPlaceModel.h"
#include "../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../Viewer/GameScene/EventViewer/EventViewerParam.h"

#include <fstream>

#if _DEBUG
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"
#include "../../Framework/Input/input.h"
#endif

using namespace EventConfig;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const char* EventCSVPath_City = "data/FIELD/City/City_Event.csv";
const char* EventCSVPath_World = "data/FIELD/World/World_Event.csv";
const char* EventCSVPath_Space = "data/FIELD/Space/Space_Event.csv";


//=============================================================================
// �R���X�g���N�^
//=============================================================================
EventController::EventController(int FieldLevel)
{
	if (FieldLevel == Field::City)
	{
		LoadCSV(EventCSVPath_City);
	}
	else if (FieldLevel == Field::World)
	{
		LoadCSV(EventCSVPath_World);
	}
	else if (FieldLevel == Field::Space)
	{
		LoadCSV(EventCSVPath_Space);
	}

	eventViewer = new EventViewer();

#if _DEBUG
	ResourceManager::Instance()->MakePolygon("Event", "data/TEXTURE/PlaceTest/Event.png", { 4.5f, 4.5f }, { 13.0f,1.0f });
	polygon = new BoardPolygon();
	polygon->SetTexDiv({ 13.0f, 1.0f });
	ResourceManager::Instance()->GetPolygon("Event", polygon);
#endif
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
EventController::~EventController()
{
	// �C�x���g�x�N�g���폜
	Utility::DeleteContainer(EventVec);
	EventCSVData.clear();

	SAFE_DELETE(eventViewer);

#if _DEBUG
	SAFE_DELETE(polygon);
#endif
}

//=============================================================================
// �X�V
//=============================================================================
void EventController::Update()
{
#if _DEBUG
	if (Keyboard::GetTrigger(DIK_F))
	{
	}
#endif

	for (auto &Event : EventVec)
	{
		if (Event->GetUse())
		{
			if (Event->GetIsPauseEvent() && !Event->GetInitialized() && !InPauseEvent)
			{
				Event->Init();
			}
			else
			{
				Event->Update();
			}
		}
		else
		{
			// �g�p�����̃C�x���g���폜
			SAFE_DELETE(Event);
		}
	}

	// �C�x���g�r���[�A�X�V
	eventViewer->Update();

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), [&](EventBase *Event)
	{
		return Event == nullptr ? true : false;
	}), std::end(EventVec));
}

//=============================================================================
// �C�x���g�I�u�W�F�N�g�`��
//=============================================================================
void EventController::DrawEventObject()
{
	// �C�x���g�I�u�W�F�N�g�`��
	for (auto &Event : EventVec)
	{
		Event->Draw();
	}

#if _DEBUG
	// �C�x���g�}�X�̉����`��
	DrawDebug();
#endif
}

//=============================================================================
// �C�x���g�r���[�A�`��
//=============================================================================
void EventController::DrawEventViewer()
{
	// �C�x���g�r���[�A�`��
	eventViewer->Draw();
}

#if _DEBUG
//=============================================================================
// �C�x���g�}�X�̉����`��
//=============================================================================
void EventController::DrawDebug()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (auto& Object : EventCSVData)
	{
		// �e�X�g�`��
		Transform transform = Transform(
			Object.Pos.ConvertToWorldPosition() + Vector3::Up,
			{ D3DXToRadian(90.0f), 0.0f, 0.0f },
			Vector3::One);

		polygon->SetTextureIndex(Object.EventType);
		polygon->Draw(transform.GetMatrix());
	}

	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
#endif

//=============================================================================
// CSV�̓ǂݍ���
//=============================================================================
void EventController::LoadCSV(const char* FilePath)
{
	//CSV�t�@�C����ǂݍ���
	std::ifstream stream(FilePath);

	std::string line;			// CSV��1�s���ǂރo�b�t�@
	const char Delim = ',';		// ��؂蕶��
	int x = 0;					// Event��X�ʒu
	int z = 0;					// Event��Z�ʒu

	//CSV�̏I���܂œǂݍ��ݑ�����
	while (std::getline(stream, line))
	{
		//1�s���ǂݍ��񂾃f�[�^����؂蕶���ŕ�������
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
}

//=============================================================================
// �C�x���g�����̊m�F
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
				Camera::TranslationPlugin* Test = Camera::TranslationPlugin::Instance();
				EventBase* Ptr = nullptr;

				// �C�x���g�C���X�^���X�쐬
				switch (EventPlace->EventType)
				{
				case LinkLevelUp:
					Ptr = new LinkLevelUpEvent();
					break;
				case NewCity:
					Ptr = new NewTownEventCtrl(eventViewer, FieldLevel);
					break;
				case StockRecovery:
					Ptr = new StockRecoveryEvent();
					break;
				case FamousPeople:
					Ptr = new FamousPeopleEvent();
					break;
				case AllLinkLevelUp:
					Ptr = new AllLinkLevelUpEvent();
					break;
				case AILevelUp:
					Ptr = new AILevelUpEvent();
					break;
				case TimeRecovery:
					Ptr = new TimeRecoveryEvent();
					break;
				case LinkLevelDecrease:
					Ptr = new LinkLevelDecreaseEvent();
					break;
				case CityDestroy:
					Ptr = new CityDestroyEvent(eventViewer);
					break;
				case AILevelDecrease:
					Ptr = new AILevelDecreaseEvent(eventViewer);
					break;
				case BanStockUse:
					if (InBanStock)
					{
						// ���X�g�b�N�g�p�֎~��
						++EventPlace;
						continue;
					}
					else
					{
						Ptr = new BanStockUseEvent(eventViewer,
							[&](bool Flag) {SetBanStock(Flag); },
							[&]() {return GetInPause(); });
					}
					break;
				default:
					break;
				}

				if (Ptr != nullptr)
				{
					// �C�x���g���b�Z�[�W�ݒu
					eventViewer->SetEventMessage(Ptr->GetEventMessage(FieldLevel));

					// �C�x���g�x�N�g���Ƀv�b�V��
					EventVec.push_back(Ptr);
				}

				// CSV�f�[�^���甭�������C�x���g�̎������폜
				EventPlace = EventCSVData.erase(EventPlace);
			}
			else
				++EventPlace;
		}
	}
}

//=============================================================================
// FieldEventHandler�̃|�C���^���󂯎��
//=============================================================================
void EventController::ReceiveFieldEventHandler(FieldEventHandler *Ptr)
{
	// FieldEventHandler�̂���֐���ݒ肷��
	Ptr->SetEventControllerInPause = [&](bool Flag)
	{
		SetInPause(Flag);
	};
	EventBase::ReceiveFieldEventHandler(Ptr);
}

//=============================================================================
// �r���[���p�����[�^���ߍ��ݏ���
//=============================================================================
void EventController::EmbedViewerParam(EventViewerParam& param)
{
	param.InBanStock = this->InBanStock;
	param.InPauseEvent = this->InPauseEvent;
}

//=============================================================================
// �X�g�b�N�g�p�֎~�̐ݒu
//=============================================================================
void EventController::SetBanStock(bool Flag)
{
	InBanStock = Flag;
}

//=============================================================================
// ���݂̓^�C���X�g�b�v�C�x���g���������Ă��邩�ǂ���
//=============================================================================
void EventController::SetInPause(bool Flag)
{
	InPauseEvent = Flag;
}

//=============================================================================
// ���݂̓^�C���X�g�b�v�C�x���g���������Ă��邩�ǂ���
//=============================================================================
bool EventController::GetInPause(void)
{
	return InPauseEvent;
}
