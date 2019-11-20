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
#include "../../../Effect/GameParticleManager.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../../Field/Camera/EventCamera.h"

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
const float FallSpeed = 4.0f;
// �f�����f���̃X�P�[��
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);

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
	camera(camera)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
NewTownEvent_Space::~NewTownEvent_Space()
{
	eventViewer = nullptr;
	NewPlanet = nullptr;
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
	PlanetPos = BuildPos + D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	MoveDirection = BuildPos - PlanetPos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

	// �f�����b�V���쐬
	PlanetModel = new PlanetActor(PlanetPos, Scale, "Town-Space");

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(EventTelop::NewPlanet, [=]()
	{
		// �\��n�ɃJ�������ړ�������
		camera->Translation(PlanetPos, 30, [&]() {FallenStart(); });
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

	float Distance = 0.0f;

	switch (EventState)
	{
		// �f���o��
	case PlanetDebut:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(PlanetPos - BuildPos));

		if (Distance > pow(4.0f, 2))
		{
			PlanetPos += MoveDirection * FallSpeed;
		}
		else
		{
			// �f�������G�t�F�N�g
			EventState = State::PlanetArrive;
		}

		camera->Translation(PlanetPos, 1, nullptr);

		break;

	default:
		break;
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

	PlanetModel->SetPosition(PlanetPos);
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
	//GameParticleManager::Instance()->SetSingularityEffect(TownPos);
}

////=============================================================================
//// �C�x���g�I������
////=============================================================================
//void NewTownEvent_Space::EventOver(void)
//{
//	// �C�x���g�I���A�Q�[�����s
//	CameraTranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}