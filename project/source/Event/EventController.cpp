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
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Particle/BaseEmitter.h"
#include "../../Framework/Network/UDPClient.h"

#include "../Field/Place/FieldPlaceModel.h"
#include "../Viewer/GameScene/Controller/EventViewer.h"
#include "../Viewer/GameScene/ParameterContainer/EventViewerParam.h"
#include "../Viewer/GameScene/Controller/BeatGameViewer.h"
#include "../Effect/GameParticleManager.h"

#include "../Field/Camera/EventCamera.h"
#include "../Reward/RewardController.h"

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
	eventViewer = new EventViewer();

	camera = new EventCamera();

	beatViewer = new BeatGameViewer();

	Init(FieldLevel);

	camera->AddPlugin(CameraShakePlugin::Instance());

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
	Uninit();

	SAFE_DELETE(eventViewer);

	SAFE_DELETE(camera);

	SAFE_DELETE(beatViewer);

#if _DEBUG
	SAFE_DELETE(polygon);
#endif
}

//=============================================================================
// ������
//=============================================================================
void EventController::Init(int FieldLevel)
{
	// �G�~�b�^�[�R���e�i�̃N���A
	for (auto&& pair : infoEmitterContainer)
	{
		if (pair.second != nullptr)
			pair.second->SetActive(false);
	}
	infoEmitterContainer.clear();

	// CSV�t�@�C����ǂݎ��
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

	beatViewer->SetFieldLevel(FieldLevel);
}

//=============================================================================
// �I��
//=============================================================================
void EventController::Uninit(void)
{
	// �C�x���g�x�N�g���폜
	Utility::DeleteContainer(EventVec);
	EventCSVData.clear();

	for (auto&& emitter : infoEmitterContainer)
	{
		if (emitter.second != nullptr)
			emitter.second->SetActive(false);
	}
	infoEmitterContainer.clear();
}

//=============================================================================
// �X�V
//=============================================================================
void EventController::Update()
{
#if _DEBUG
	if (Keyboard::GetTrigger(DIK_F))
	{
		//EventVec.push_back(new NewTownEventCtrl(eventViewer, Field::Space, camera));
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

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), [&](EventBase *Event)
	{
		return Event == nullptr ? true : false;
	}), std::end(EventVec));

	//�C�x���g�J�����X�V
	camera->Update();
}

//=============================================================================
// �C�x���g�r���[���X�V
//=============================================================================
void EventController::UpdateViewer(void)
{
	// �C�x���g�r���[�A�X�V
	eventViewer->Update();
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
	//�r�[�g�r���[�A�`��
	beatViewer->Draw();

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
				infoEmitterContainer[Pos] = GameParticleManager::Instance()->Generate(GameParticle::EventInfo, Pos.ConvertToWorldPosition());
			}
			x++;
		}
		z++;
	}
}

//=============================================================================
// �C�x���g�����̊m�F
//=============================================================================
bool EventController::CheckEventHappen(const std::vector<Field::Model::PlaceModel*>& RoutePtr, int FieldLevel)
{
	bool flgPause = false;

	for (auto &place : RoutePtr)
	{
		Field::FieldPosition PlacePos = place->GetPosition();
		for (auto EventPlace = EventCSVData.begin(); EventPlace != EventCSVData.end();)
		{
			if (PlacePos.x == EventPlace->Pos.x && PlacePos.z == EventPlace->Pos.z)
			{
				CameraTranslationPlugin* Test = CameraTranslationPlugin::Instance();
				EventBase* Ptr = nullptr;

				// �C�x���g�C���X�^���X�쐬
				switch (EventPlace->EventType)
				{
				case LinkLevelUp:
					Ptr = new LinkLevelUpEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, LinkLevelUp);
					break;
				case NewCity:
					Ptr = new NewTownEventCtrl(eventViewer, FieldLevel, camera);
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, NewCity);
					flgPause = true;
					break;
				case StockRecovery:
					Ptr = new StockRecoveryEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, StockRecovery);
					break;
				case FamousPeople:
					Ptr = new FamousPeopleEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, FamousPeople);
					break;
				case AllLinkLevelUp:
					Ptr = new AllLinkLevelUpEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, AllLinkLevelUp);
					break;
				case AILevelUp:
					Ptr = new AILevelUpEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, AILevelUp);
					break;
				case TimeRecovery:
					Ptr = new TimeRecoveryEvent();
					RewardController::Instance()->SetRewardData(RC::Type::PlusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::PlusComplete, TimeRecovery);
					break;
				case LinkLevelDecrease:
					Ptr = new LinkLevelDecreaseEvent();
					RewardController::Instance()->SetRewardData(RC::Type::MinusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::MinusComplete, LinkLevelDecrease - 7);
					break;
				case CityDestroy:
					Ptr = new CityDestroyEvent(eventViewer, beatViewer, camera);
					RewardController::Instance()->SetRewardData(RC::Type::MinusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::MinusComplete, CityDestroy - 7);
					flgPause = true;
					break;
				case AILevelDecrease:
					Ptr = new AILevelDecreaseEvent(eventViewer, camera, beatViewer);
					RewardController::Instance()->SetRewardData(RC::Type::MinusMaster, 1);
					RewardController::Instance()->SetRewardData(RC::Type::MinusComplete, AILevelDecrease - 7);
					flgPause = true;
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
							beatViewer,
							[&](bool Flag) {SetBanStock(Flag); },
							[&]() {return GetInPause(); });
						RewardController::Instance()->SetRewardData(RC::Type::MinusMaster, 1);
						RewardController::Instance()->SetRewardData(RC::Type::MinusComplete, BanStockUse - 7);
						flgPause = true;
					}
					break;
				default:
					break;
				}

				if (Ptr != nullptr)
				{
					// �C�x���g���b�Z�[�W�ݒu
					eventViewer->SetEventMessage(Ptr->GetEventMessage(FieldLevel));

					// �C�x���g���p�p�P�b�g�𑗐M
					if (flgPause)
					{
						UDPClient::SendEventPacket(EventPlace->EventType, FieldLevel);
					}

					// �C�x���g�x�N�g���Ƀv�b�V��
					EventVec.push_back(Ptr);
				}

				// CSV�f�[�^���甭�������C�x���g�̎������폜
				EventPlace = EventCSVData.erase(EventPlace);

				//�C�x���g�C���t�H�̃G�~�b�^���~z
				infoEmitterContainer[PlacePos]->SetActive(false);
				infoEmitterContainer.erase(PlacePos);
			}
			else
				++EventPlace;
		}
	}

	return flgPause;
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
	param.isStockSealed = this->InBanStock;
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

//=============================================================================
// �C�x���g�̊m�F�p�f�o�b�O
//=============================================================================
bool EventController::EventDebug(int FieldLevel)
{
	EventBase* Ptr = nullptr;
	bool flgPause = false;

	// �C�x���g�C���X�^���X�쐬
	if (Debug::Button("LinkLevel Up"))
	{
		Ptr = new LinkLevelUpEvent();
	}
	if (Debug::Button("New Town"))
	{
		Ptr = new NewTownEventCtrl(eventViewer, FieldLevel, camera);
		flgPause = true;
	}
	if (Debug::Button("Stock Recovery"))
	{
		Ptr = new StockRecoveryEvent();
	}
	if (Debug::Button("Famout people"))
	{
		Ptr = new FamousPeopleEvent();
	}
	if (Debug::Button("All LinlLevel Up"))
	{
		Ptr = new AllLinkLevelUpEvent();
	}
	if (Debug::Button("AI Level Up"))
	{
		Ptr = new AILevelUpEvent();
	}
	if (Debug::Button("Time Recovery"))
	{
		Ptr = new TimeRecoveryEvent();
	}
	if (Debug::Button("LinkLevel Decrease"))
	{
		Ptr = new LinkLevelDecreaseEvent();
	}
	if (Debug::Button("City Destroy"))
	{
		Ptr = new CityDestroyEvent(eventViewer, beatViewer, camera);
		flgPause = true;
	}
	if (Debug::Button("AI Level Decrease"))
	{
		Ptr = new AILevelDecreaseEvent(eventViewer, camera, beatViewer);
		flgPause = true;
	}
	if (Debug::Button("Ban StockUse"))
	{
		Ptr = new BanStockUseEvent(eventViewer,
			beatViewer,
			[&](bool Flag) {SetBanStock(Flag); },
			[&]() {return GetInPause(); });
		flgPause = true;
	}

	if (Ptr != nullptr)
	{
		// �C�x���g���b�Z�[�W�ݒu
		eventViewer->SetEventMessage(Ptr->GetEventMessage(FieldLevel));

		// �C�x���g�x�N�g���Ƀv�b�V��
		EventVec.push_back(Ptr);
	}

	return flgPause;
}