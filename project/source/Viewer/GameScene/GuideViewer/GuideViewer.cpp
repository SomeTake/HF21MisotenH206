//=====================================
//
// �K�C�h�r���A�[[GuideViewer.cpp]
// �@�\�F�K�C�h���L�����N�^�[�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GuideViewer.h"
#include "GuideCallOutViewer.h"
#include "../../../../Framework/Resource/ResourceManager.h"
#include "../../../../Framework/Effect/RendererEffect.h"
#include "GuideCamera.h"
#include "GuideViewerBG.h"
#include "../../../SubScreen/SubScreen.h"

#ifdef _DEBUG

#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Input/input.h"

#endif

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const D3DXVECTOR2 GuideViewer::SubScreenSize = D3DXVECTOR2(360.0f, 360.0f);
const D3DXVECTOR2 GuideViewer::SubScreenPosition = D3DXVECTOR2(30.0f, 690.0f);

//=====================================
// �R���X�g���N�^
//=====================================
GuideViewer::GuideViewer()
{
	// �`��p�T�u�X�N���[���̍쐬
	subScreen = new SubScreen(SubScreenSize, SubScreenPosition);
	camera = new GuideCamera();

	// ���\�[�X�ǂݍ���
	ResourceManager::Instance()->MakePolygon("GuideViewerBG", "data/TEXTURE/VIewer/GameViewer/GuideViewer/Circuit.jpg", D3DXVECTOR2(100.0f, 100.0f));

	// �e��C���X�^���X�̍쐬
	actor = new GuideActor();
	bg = new GuideViewerBG();
	filter = new CRTFilter((DWORD)SubScreenSize.x, (DWORD)SubScreenSize.y);
	callOutViewer = new GuideCallOutViewer();
}

//=====================================
// �f�X�g���N�^
//=====================================
GuideViewer::~GuideViewer()
{
	SAFE_DELETE(subScreen);

	SAFE_DELETE(actor);
	SAFE_DELETE(camera);
	SAFE_DELETE(bg);
	SAFE_DELETE(filter);

	SAFE_DELETE(callOutViewer);
}

//=====================================
// �X�V
//=====================================
void GuideViewer::Update()
{

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_G))
	{
		SetGuideViewer("�e�X�g���Đ����ł��`\n�撣���ĉ������`");
	}

#endif

	camera->Update();
	actor->Update();
	bg->Update();
	filter->SetTime();
	filter->SetScreenParam(SubScreenSize.x, SubScreenSize.y);
	callOutViewer->Update();
}

//=====================================
// �`��
//=====================================
void GuideViewer::Draw()
{
	if (!isActive)
		return;

	const D3DXCOLOR BackColor = D3DXCOLOR(0.6f, 0.6f, 1.0f, 0.8f);
	subScreen->DrawBegin(BackColor);

	const Camera *defaultCamera = Camera::MainCamera();
	Camera::SetMainCamera(camera);
	camera->Set();

	RendererEffect::SetView(camera->GetViewMtx());
	RendererEffect::SetProjection(camera->GetProjectionMtx());

	// �C���X�^���X�̕`��
	bg->Draw();
	actor->Draw();

	for (int i = 0; i < 4; i++)
	{
		subScreen->DrawTexture();
		filter->Draw(i);
	}

	subScreen->DrawEnd();

	//�J�����𕜌�
	Camera::SetMainCamera(const_cast<Camera*>(defaultCamera));
	RendererEffect::SetView(defaultCamera->GetViewMtx());
	RendererEffect::SetProjection(defaultCamera->GetProjectionMtx());

	//////////////�ȉ��A�r���A�[����/////////////////////
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	callOutViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// �A�N�^�[�̃A�j���[�V�����؂�ւ�
//=====================================
void GuideViewer::ChangeAnim(GuideActor::AnimState next)
{
	actor->ChangeAnim(next);
}

//=====================================
// �`��۔���̃Z�b�g
//=====================================
void GuideViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=====================================
// �K�C�h�r���A�[�Z�b�g����
//=====================================
void GuideViewer::SetGuideViewer(const std::string &message)
{
	// �C�x���g���b�Z�[�W������������s
	if (message.empty()) return;

	ChangeAnim(GuideActor::AnimState::TalkingTypeB);

	callOutViewer->Set(message);
}