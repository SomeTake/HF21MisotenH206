//=============================================================================
//
// �����ŃC�x���g�N���X [CityDestroyEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "CityDestroyEvent.h"
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
const int EscapeTime = 10;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
#if _DEBUG
LPDIRECT3DDEVICE9 CityDestroyEvent::Device = nullptr;
LPD3DXMESH CityDestroyEvent::SphereMesh = nullptr;
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
	TelopOver(false),
	CountOver(false),
	RemainFrame(EscapeTime * 30)
{
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

	// �j�󂷂钬�̗\��n���擾
	//DestroyTown = fieldEventHandler->GetDestroyTarget();
	//GoalPos = DestroyTown->GetPosition().ConvertToWorldPosition();

	// �Q�[���i�s��~
	fieldEventHandler->PauseGame();

	// �e���b�v�ݒu
	eventViewer->SetEventTelop(NegativeEvent01, [&]()
	{
		fieldEventHandler->ResumeGame();
		Countdown();
	});

	//Pos = GoalPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	//FallDirection = GoalPos - Pos;
	//D3DXVec3Normalize(&FallDirection, &FallDirection);

	// �f�o�C�X�擾
	if (Device == nullptr)
	{
		Device = GetDevice();
	}

	//// ���̃��b�V�����쐬����
	//if (SphereMesh == nullptr)
	//{
	//	D3DXCreateSphere(Device, MeteoriteRadius, 16, 16, &SphereMesh, NULL);
	//}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void CityDestroyEvent::Update()
{
	//float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(GoalPos - Pos));

	//if (Distance > pow(3.0f, 2))
	//{
	//	Pos += FallDirection * FallSpeed;
	//}
	//else
	//{
	//	//fieldEventHandler->DestroyTown();
	//	this->UseFlag = false;
	//}

	if (TelopOver)
	{
		RemainFrame--;
		if (RemainFrame <= 0)
		{
			CountOver;
			fieldEventHandler->PauseGame();
			Camera::TranslationPlugin::Instance()->Move(GoalPos, 30, []()
			{
				// �����_��

			});
			UseFlag = false;
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CityDestroyEvent::Draw()
{
	//D3DXMATRIX WorldMatrix, TransMatrix;

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&WorldMatrix);

	//// �ړ��𔽉f
	//D3DXMatrixTranslation(&TransMatrix, Pos.x, Pos.y, Pos.z);
	//D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	//// �}�e���A���̐ݒ�
	//Device->SetMaterial(&Material);

	//// ���̕`��
	//SphereMesh->DrawSubset(0);

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

//=============================================================================
// 覐΂�����܂ł̃J�E���g�_�E��
//=============================================================================
void CityDestroyEvent::Countdown(void)
{
	this->TelopOver = true;
}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string CityDestroyEvent::GetEventMessage(int FieldLevel)
{
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
}
