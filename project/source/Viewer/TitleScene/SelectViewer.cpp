//=====================================
//
// �Z���N�g�r���A�[[SelectViewer.cpp]
// �@�\�F���[�h�Z���N�g�\���p
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "SelectViewer.h"
#include "../../SubScreen/SubScreen.h"
#include "SelectCamera.h"
#include "../../../Framework/Effect/RendererEffect.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "SelectLogo.h"

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const D3DXVECTOR2 SelectViewer::SubScreenSize = D3DXVECTOR2(960.0f, 640.0f);
const D3DXVECTOR2 SelectViewer::SubScreenPos = D3DXVECTOR2((float)SCREEN_CENTER_X - 480.0f, (float)SCREEN_CENTER_Y);

//=====================================
// �R���X�g���N�^
//=====================================
SelectViewer::SelectViewer()
{
	// �T�u�X�N���[�����쐬
	subScreen = new SubScreen(SubScreenSize, SubScreenPos);
	camera = new SelectCamera();

	// ���\�[�X�ǂݍ���
	ResourceManager::Instance()->MakePolygon("ModeSelect", "data/TEXTURE/Title/ModeSelect.png", D3DXVECTOR2(50.0f, 16.7f), D3DXVECTOR2(1.0f, 3.0f));

	// �e��C���X�^���X�̍쐬
	logo[GameStart] = new SelectLogo();
	logo[GameStart]->LoadResource("ModeSelect");
	logo[GameStart]->SetTextureIndex(0);
	logo[GameStart]->SetPosition(Vector3::Zero);
	logo[TrophyCheck] = new SelectLogo();
	logo[TrophyCheck]->LoadResource("ModeSelect");
	logo[TrophyCheck]->SetPosition(Vector3::Zero);
	logo[TrophyCheck]->SetTextureIndex(1);
	logo[Exit] = new SelectLogo();
	logo[Exit]->LoadResource("ModeSelect");
	logo[Exit]->SetPosition(Vector3::Zero);
	logo[Exit]->SetTextureIndex(2);
}

//=====================================
// �f�X�g���N�^
//=====================================
SelectViewer::~SelectViewer()
{
	SAFE_DELETE(subScreen);
	SAFE_DELETE(camera);
	for (int i = 0; i < Mode::Max; i++)
	{
		SAFE_DELETE(logo[Mode(i)]);
	}
}

//=====================================
// �R���X�g���N�^
//=====================================
void SelectViewer::Update()
{
	camera->Update();

	for (int i = 0; i < Mode::Max; i++)
	{
		logo[Mode(i)]->Update();
	}
}

void SelectViewer::Draw()
{
	const D3DXCOLOR BackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	subScreen->DrawBegin(BackColor);

	const Camera *defaultCamera = Camera::MainCamera();
	Camera::SetMainCamera(camera);
	camera->Set();

	RendererEffect::SetView(camera->GetViewMtx());
	RendererEffect::SetProjection(camera->GetProjectionMtx());

	// �C���X�^���X�̕`��
	for (int i = 0; i < Mode::Max; i++)
	{
		logo[Mode(0)]->Draw();
	}

	subScreen->DrawTexture();

	subScreen->DrawEnd();

	// �J��������
	Camera::SetMainCamera(const_cast<Camera*>(defaultCamera));
	RendererEffect::SetView(defaultCamera->GetViewMtx());
	RendererEffect::SetProjection(defaultCamera->GetProjectionMtx());
}
