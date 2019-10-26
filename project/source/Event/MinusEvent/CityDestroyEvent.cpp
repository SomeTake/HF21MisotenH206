//=============================================================================
//
// �����ŃC�x���g�N���X [CityDestroyEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "CityDestroyEvent.h"
#include "BeatGame.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Viewer/Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Viewer/Framework/ViewerDrawer/countviewerdrawer.h"

#include "../../../Framework/Camera/CameraTranslationPlugin.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// 覐΂̔��a
const float MeteoriteRadius = 3.0f;
const float MeteoriteDistance = 200.0f;
const float FallSpeed = 4.0f;
// 覐΂�����܂ł̎���
const int EscapeTime = 10;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
#if _DEBUG
LPD3DXMESH CityDestroyEvent::SphereMesh = nullptr;
LPD3DXMESH CityDestroyEvent::MissileMesh = nullptr;
D3DMATERIAL9 CityDestroyEvent::Material =
{
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// Diffuse color RGBA
	D3DXCOLOR(1.0f, 0.65f, 0.0f, 1.0f),	// Ambient color RGB
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Specular 'shininess'
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Emissive color RGB
	0.0f,								// Sharpness if specular highlight 
};
#endif

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CityDestroyEvent::CityDestroyEvent(EventViewer* eventViewer) :
	EventAvoid(false),
	BeatGameOver(false)
	//CountOver(false),
	//TelopOver(false),
	//RemainFrame(EscapeTime * 30)
{
#if 0
	//������
	intNum = new CountViewerDrawer();
	intNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	intNum->MakeVertex();
	intNum->size = D3DXVECTOR3(60.0f, 60.0f, 0.0f);
	intNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	intNum->position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 140.0f, SCREEN_HEIGHT / 10 * 2.0f + 20.0f, 0.0f);
	intNum->SetColor(SET_COLOR_NOT_COLORED);
	intNum->intervalNumberScr = 80.0f;
	intNum->intervalNumberTex = 0.1f;
	intNum->placeMax = 2;
	intNum->baseNumber = 10;

	//������
	fewNum = new CountViewerDrawer();
	fewNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	fewNum->MakeVertex();
	fewNum->size = D3DXVECTOR3(30.0f, 30.0f, 0.0f);
	fewNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fewNum->position = D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, SCREEN_HEIGHT / 10 * 2.0f + 30.0f, 0.0f);
	fewNum->SetColor(SET_COLOR_NOT_COLORED);
	fewNum->intervalNumberScr = 40.0f;
	fewNum->intervalNumberTex = 0.1f;
	fewNum->placeMax = 2;
	fewNum->baseNumber = 10;

	//�����_
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Point.png");
	point->MakeVertex();
	point->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10 * 2.0f, 0.0f);
	point->SetColor(SET_COLOR_NOT_COLORED);

#endif

	// �A�ŃQ�[���C���X�^���X
	beatGame = new BeatGame(eventViewer, [&](bool EventAvoid) { UseMissile(EventAvoid); });

	// �j�󂷂钬�̗\��n���擾
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();
	MissilePos = TownPos;

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(NegativeEvent01, [&]()
	{
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]()
		{
			CountdownStart();
		});
	});

	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

#if _DEBUG
	// ���̃��b�V�����쐬����
	if (SphereMesh == nullptr)
	{
		LPDIRECT3DDEVICE9 Device = GetDevice();
		D3DXCreateSphere(Device, MeteoriteRadius, 16, 16, &SphereMesh, NULL);
		D3DXCreateSphere(Device, 1.0f, 16, 16, &MissileMesh, NULL);
	}
#endif
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{
	SAFE_DELETE(beatGame);
	SAFE_DELETE(point);
	SAFE_DELETE(fewNum);
	SAFE_DELETE(intNum);
}

//=============================================================================
// �X�V
//=============================================================================
void CityDestroyEvent::Update()
{
	if (!BeatGameOver)
	{
		beatGame->Update();
	}
	else
	{
		if (EventAvoid)
		{
			// =================
			// �~�T�C������
			// =================
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - MissilePos));

			if (Distance > pow(3.0f, 2))
			{
				MissilePos += MoveDirection * FallSpeed;
				MeteoritePos += -MoveDirection * FallSpeed;
				Camera::TranslationPlugin::Instance()->Move(MissilePos, 1, nullptr);
			}
			else
			{
				// 覐Δ����G�t�F�N�g
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				this->UseFlag = false;
			}
		}
		else
		{
			// =================
			// 覐Η���
			// =================
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

			if (Distance > pow(3.0f, 2))
			{
				MeteoritePos += MoveDirection * FallSpeed;
			}
			else
			{
				// �����ŃG�t�F�N�g
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				// �����ŏ���
				fieldEventHandler->DestroyTown(Target);

				this->UseFlag = false;
			}
		}
	}

#if 0
	if (!CountOver)
	{
		RemainFrame--;
		if (RemainFrame <= 0)
		{
			CountOver = true;
			fieldEventHandler->PauseGame();
			Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]()
			{
				// �n���h�q�R�g�p
				if (fieldEventHandler->TryUsingEDF())
				{
					// �~�T�C���g�p
					UseMissile(true);
				}
				else
				{
					UseMissile(false);
				}
			});
		}
	}
	else
	{
		if (EventAvoid)
		{
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - MissilePos));

			if (Distance > pow(3.0f, 2))
			{
				MissilePos += MoveDirection * FallSpeed;
				MeteoritePos += -MoveDirection * FallSpeed;
				Camera::TranslationPlugin::Instance()->Move(MissilePos, 1, nullptr);
			}
			else
			{
				// 覐Δ����G�t�F�N�g
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				this->UseFlag = false;
			}
		}
		else
		{
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

			if (Distance > pow(3.0f, 2))
			{
				MeteoritePos += MoveDirection * FallSpeed;
			}
			else
			{
				// �����ŃG�t�F�N�g
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				this->UseFlag = false;
			}
		}
}
#endif

	if (!UseFlag)
	{
		// �C�x���g�I���A�Q�[�����s
		fieldEventHandler->ResumeGame();
	}
}

//=============================================================================
// �`��
//=============================================================================
void CityDestroyEvent::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	beatGame->Draw();

#if _DEBUG
	D3DXMATRIX WorldMatrix, TransMatrix;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMatrix);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&TransMatrix, MeteoritePos.x, MeteoritePos.y, MeteoritePos.z);
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

	// ���[���h�}�g���b�N�X�̐ݒ�
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// �}�e���A���̐ݒ�
	Device->SetMaterial(&Material);

	// ���̕`��
	SphereMesh->DrawSubset(0);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&WorldMatrix);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&TransMatrix, MissilePos.x, MissilePos.y, MissilePos.z);
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

	// ���[���h�}�g���b�N�X�̐ݒ�
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// �~�T�C���`��
	MissileMesh->DrawSubset(0);
#endif

#if 0
	if (!CountOver)
	{
		Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		Device->SetRenderState(D3DRS_ALPHAREF, 0);
		Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		//�����_
		point->Draw();
		point->SetVertex();

		float RemainTime = RemainFrame / 30.0f;

		//������
		intNum->DrawCounter(intNum->baseNumber, (int)RemainTime, intNum->placeMax,
			intNum->intervalNumberScr, intNum->intervalNumberTex);

		//������
		fewNum->DrawCounter(fewNum->baseNumber, (int)((RemainTime - (int)RemainTime)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
			fewNum->intervalNumberScr, fewNum->intervalNumberTex);

		Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
	else
	{
#if _DEBUG
		D3DXMATRIX WorldMatrix, TransMatrix;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&WorldMatrix);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&TransMatrix, MeteoritePos.x, MeteoritePos.y, MeteoritePos.z);
		D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

		// ���[���h�}�g���b�N�X�̐ݒ�
		Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

		// �}�e���A���̐ݒ�
		Device->SetMaterial(&Material);

		// ���̕`��
		SphereMesh->DrawSubset(0);

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&WorldMatrix);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&TransMatrix, MissilePos.x, MissilePos.y, MissilePos.z);
		D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

		// ���[���h�}�g���b�N�X�̐ݒ�
		Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

		// �~�T�C���`��
		MissileMesh->DrawSubset(0);
#endif
}
#endif
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string CityDestroyEvent::GetEventMessage(int FieldLevel)
{
#if 0
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("���̒��͕����΂ɂ��悤");
	}
	else if (FieldLevel == Field::Model::World)
	{

	}
	else if (FieldLevel == Field::Model::Space)
	{

	}

	if (!MessageContainer.empty())
	{
		int MessageNo = rand() % MessageContainer.size();
		return MessageContainer.at(MessageNo);
	}
	else
	{
		string ErrMsg = "�C�x���g���b�Z�[�W������܂���";
		return ErrMsg;
	}
#endif
	// �k��
	return "";
}


//=============================================================================
// 覐΂�����܂ł̃J�E���g�_�E��
//=============================================================================
void CityDestroyEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
}

//=============================================================================
// �~�T�C������
//=============================================================================
void CityDestroyEvent::UseMissile(bool Flag)
{
	BeatGameOver = true;

	if (!Flag)
	{
		EventAvoid = false;
		return;
	}
	else
	{
		EventAvoid = true;
		MoveDirection = D3DXVECTOR3(MeteoritePos - MissilePos);
		D3DXVec3Normalize(&MoveDirection, &MoveDirection);
	}
}
