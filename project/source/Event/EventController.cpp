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
#include "PlusEvent/NewCityEvent.h"
#include "PlusEvent/StockRecoveryEvent.h"
#include "MinusEvent/AILevelDecreaseEvent.h"
#include "MinusEvent/BanStockUseEvent.h"
#include "MinusEvent/CityDestroyEvent.h"
#include "MinusEvent/LinkLevelDecreaseEvent.h"
#include "MinusEvent/CongestionUpEvent.h"
#include "MinusEvent/MoveInverseEvent.h"

#include "../../Framework/Core/Utility.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../Framework/Camera/CameraShakePlugin.h"

#include "../Field/Place/FieldPlaceModel.h"
//�C�x���g�r���[�A�i���[�͂ܒǋL�j
#include "../Viewer/GameScene/EventViewer/EventViewer.h"

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
// �g�p���Ă��Ȃ��C�x���g���폜
bool RemoveCondition(EventBase *Event) { return Event == nullptr ? true : false; }

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
EventController::EventController(int FieldLevel) : FieldLevel(FieldLevel)
{
	LoadCSV("data/FIELD/sample01_Event.csv");

	eventViewer = new EventViewer();

#if _DEBUG
	ResourceManager::Instance()->MakePolygon("Event", "data/TEXTURE/PlaceTest/Event.png", { 4.5f, 4.5f }, { 13.0f,1.0f });
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

	fieldController = nullptr;

	SAFE_DELETE(eventViewer);
}

//=============================================================================
// �X�V
//=============================================================================
void EventController::Update()
{
#if _DEBUG
	if (Keyboard::GetTrigger(DIK_F))
	{
		EventVec.push_back(new CityDestroyEvent(eventViewer));
	}
#endif

	for (auto &Event : EventVec)
	{
		if (Event->GetUse())
		{
			Event->Update();
		}
		else
		{
			// �g�p�����̃C�x���g���폜
			SAFE_DELETE(Event);
		}
	}

	// �C�x���g�r���[�A�X�V
	eventViewer->Update();

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), RemoveCondition), std::end(EventVec));
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
		//�e�X�g�`��
		Transform transform = Transform(
			Object.Pos.ConvertToWorldPosition() + Vector3::Up,
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
// CSV�̓ǂݍ���
//=============================================================================
void EventController::LoadCSV(const char* FilePath)
{
	//�������ς݂ł���΃��^�[��
	//if (initialized)
	//	return;

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

	//����������
	//initialized = true;
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
					Ptr = new NewCityEvent(eventViewer);
					break;
				case StockRecovery:
					Ptr = new StockRecoveryEvent();
					break;
				case FamousPeople:
					Ptr = new FamousPeopleEvent(150);
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
					Ptr = new AILevelDecreaseEvent();
					break;
				case MoveInverse:
					Ptr = new MoveInverseEvent(300);
					break;
				case BanStockUse:
					Ptr = new BanStockUseEvent(300);
					break;
				case CongestionUp:
					Ptr = new CongestionUpEvent(300);
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

					// CSV�f�[�^���甭�������C�x���g�̎������폜
					EventPlace = EventCSVData.erase(EventPlace);
				}
			}
			else
				++EventPlace;
		}
	}
}

//=============================================================================
// FieldController�̃|�C���^���󂯎��
//=============================================================================
void EventController::ReceiveFieldEventHandler(FieldEventHandler *Ptr)
{
	EventBase::ReceiveFieldEventHandler(Ptr);
}