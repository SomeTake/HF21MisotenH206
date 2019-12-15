//=============================================================================
//
// �V������(�F�����x��)�C�x���g�N���X [NewTownEvent_Space.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_Space.h"
#include "../../EventActor/PlanetActor.h"
#include "../../../Viewer/GameScene/EventViewer/EventTelop.h"
#include "../../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../../Effect/SpaceParticleManager.h"
#include "../../../Field/Camera/EventCamera.h"

#include "../../../../Framework/Task/TaskManager.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Sound/SoundEffect.h"
#include "../../../Sound/SoundConfig.h"

enum State
{
	TelopExpanding,
	PlanetDebut,
	PlanetArrive,
};
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �������x
const int FallFrame = 90;
// �f�����f���̃X�P�[��
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
NewTownEvent_Space::NewTownEvent_Space(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera *camera) :
	EventBase(true),
	eventViewer(Ptr),
	EventState(TelopExpanding),
	EventOverFunc(EventOverFunc),
	camera(camera),
	CountFrame(0)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
NewTownEvent_Space::~NewTownEvent_Space()
{
	eventViewer = nullptr;
	NewPlanet = nullptr;
	camera = nullptr;
	MoveTailEmitter = nullptr;
	StarDustEmitter = nullptr;
	SAFE_DELETE(PlanetModel);
}

//=============================================================================
// ������
//=============================================================================
void NewTownEvent_Space::Init()
{
	// �V�����f�������\����W���擾
	NewPlanet = fieldEventHandler->GetNewTownPosition();
	BuildPos = NewPlanet->GetPosition().ConvertToWorldPosition();

	// �f�����������v�Z
	StartPos = BuildPos + D3DXVECTOR3(100.0f, 100.0f, -100.0f);

	// �f�����b�V���쐬
	PlanetModel = new PlanetActor(StartPos, Scale, "Space-Town");

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::NewPlanet, [=]()
	{
		// �f���ɃJ�������ړ�������
		camera->Translation(StartPos, 30, [&]() {FallenStart(); });
	});

	// �������I��
	Initialized = true;
}

//=============================================================================
// �X�V
//=============================================================================
void NewTownEvent_Space::Update()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	if (EventState == PlanetDebut)
	{
		CountFrame++;
		float Time = (float)CountFrame / (float)FallFrame;

		// �f���ړ�
		D3DXVECTOR3 PlanetPos = Easing::EaseValue(Time, StartPos, BuildPos, EaseType::OutQuart);
		PlanetModel->SetPosition(PlanetPos);
		MoveTailEmitter->SetPosition(PlanetPos);
		StarDustEmitter->SetPosition(PlanetPos);

		// �J�����ݒu
		camera->Translation(PlanetPos, 1, nullptr);

		// �I������
		if (CountFrame >= FallFrame)
		{
			EventState = PlanetArrive;
			TaskManager::Instance()->CreateDelayedTask(30, [&]()
			{
				// �f���ǉ�
				fieldEventHandler->CreateNewTown(NewPlanet);
				// �J�������A
				camera->Return(15, EventOverFunc);
			});
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void NewTownEvent_Space::Draw()
{
	// �܂����������Ă��Ȃ�
	if (!Initialized)
		return;

	PlanetModel->Draw();
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string NewTownEvent_Space::GetEventMessage(int FieldLevel)
{
	// �k��
	return "";
}

//=============================================================================
// �f�������J�n
//=============================================================================
void NewTownEvent_Space::FallenStart(void)
{
	EventState = PlanetDebut;

	// �f�������G�t�F�N�g
	SpaceParticleManager::Instance()->SetPlanetFallEffect(StartPos, &MoveTailEmitter, &StarDustEmitter);

	SE::Play(SoundConfig::SEID::NewStarSE, 1.0f);
	TaskManager::Instance()->CreateDelayedTask(90, [&]()
	{
		SE::Play(SoundConfig::SEID::CreationEvent, 1.0f);
	});

}