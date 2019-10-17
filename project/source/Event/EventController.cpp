//=============================================================================
//
// �C�x���g�R���g���[���[�N���X [EventController.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "EventController.h"
#include "EventConfig.h"
#include "MinusEvent/CityDestroyEvent.h"


#include "../../Framework/Core/Utility.h"
#include "../../Framework/String/String.h"

#include <fstream>
#include <string>

#if _DEBUG
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"
#endif

using namespace EventConfig;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �g�p���Ă��Ȃ��C�x���g���폜
//bool RemoveCondition(EventBase *Event) { return !Event->GetUse(); }
bool RemoveCondition(EventBase *Event) { return Event == nullptr ? true : false; }

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//std::vector<Field::Model::PlaceModel*> *EventController::route = nullptr;
std::vector<EventInfo> EventController::EventCSVData;
std::vector<EventBase*> EventController::EventVec;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
EventController::EventController(int FieldLevel) : FieldLevel(FieldLevel)
{
	LoadCSV("data/FIELD/sample01_Event.csv");

#if _DEBUG
	ResourceManager::Instance()->MakePolygon("Event", "data/TEXTURE/PlaceTest/Event.png", { 4.5f, 4.5f }, { 12.0f,1.0f });
#endif
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
EventController::~EventController()
{
	// �C�x���g�x�N�g���폜
	Utility::DeleteContainer(EventVec);
}

//=============================================================================
// �X�V
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
			SAFE_DELETE(Event);
		}
	}

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), RemoveCondition), std::end(EventVec));
}

//=============================================================================
// �`��
//=============================================================================
void EventController::Draw()
{
	for (auto &Event : EventVec)
	{
		Event->Draw();
	}

#if _DEBUG
	DrawDebug();
#endif
}

#if _DEBUG
//=============================================================================
// �C�x���g�}�X�`��
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
			{ Object.x * 10.0f, 1.0f, Object.z * -10.0f },
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
				EventCSVData.push_back(EventInfo{ x, z, Type });
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
		Field::FieldPosition Pos = place->GetPosition();
		for (auto EventPlace = EventCSVData.begin(); EventPlace != EventCSVData.end();)
		{
			if (Pos.x == EventPlace->x && Pos.z == EventPlace->z)
			{
				switch (EventPlace->EventType)
				{
				case CityLevelUp:
					break;
				case NewCity:
					break;
				case ChipRecovery:
					break;
				case FamousPeople:
					break;
				case Bonus:
					break;
				case AILevelUp:
					break;
				case CityLevelDecrease:
					break;
				case CityDestroy:
					EventVec.push_back(new CityDestroyEvent(FieldLevel, Vector3::Zero));
					break;
				case AILevelDecrease:
					break;
				case MoveInverse:
					break;
				case BanSpecialChip:
					break;
				case CongestionUp:
					break;
				default:
					break;
				}

				EventPlace = EventCSVData.erase(EventPlace);
			}
			else
				++EventPlace;
		}
	}
}
