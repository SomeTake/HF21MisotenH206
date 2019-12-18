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
#include <algorithm>

#ifdef _DEBUG

#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Input/input.h"

#endif

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const D3DXVECTOR2 GuideViewer::SubScreenSize = D3DXVECTOR2(360.0f, 360.0f);
const D3DXVECTOR2 GuideViewer::SubScreenPosition = D3DXVECTOR2(50.0f, 670.0f);

//=====================================
// ������
//=====================================
void GuideViewer::Init()
{
	// �`��p�T�u�X�N���[���̍쐬
	subScreen = new SubScreen(SubScreenSize, SubScreenPosition);
	camera = new GuideCamera();

	// ���\�[�X�ǂݍ���
	//ResourceManager::Instance()->MakePolygon("GuideViewerBG", "data/TEXTURE/VIewer/GameViewer/GuideViewer/Circuit.jpg", D3DXVECTOR2(100.0f, 100.0f));

	// �e��C���X�^���X�̍쐬
	actor = new GuideActor();
	bg = new GuideViewerBG();
	filter = new CRTFilter((DWORD)SubScreenSize.x, (DWORD)SubScreenSize.y);
	callOutViewer = new GuideCallOutViewer();
	prev = SoundConfig::SEID::AIBonus;
	cntQue = 0;
}

//=====================================
// �폜
//=====================================
void GuideViewer::Uninit()
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
		SetMessage("�e�X�g���Đ����ł��`\n�撣���ĉ������`");
	}

#endif

	camera->Update();
	UpdateDeque();
	D3DXVECTOR3 test = camera->UnProjection(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f);
	D3DXVECTOR3 test2 = camera->UnProjection(D3DXVECTOR3(SubScreenSize.x, SubScreenSize.y, 0.0f), 0.0f);
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
// �L���[�Ƀf�[�^���Z�b�g
//=====================================
void GuideViewer::SetData(const std::string& message, GuideActor::AnimState next, SoundConfig::SEID voice)
{
	que.push_back(new GuideViewerData(message, next, voice));
}

//=====================================
// �L���[�̍X�V
//=====================================
void GuideViewer::UpdateDeque()
{
	if (!isActive)
		return;

	cntQue++;
	
	// �����{�C�X�������ꍇ�A�폜
	que.erase(std::unique(que.begin(), que.end(), [](GuideViewerData* a, GuideViewerData* b) {
		return (a->voice == b->voice);
	}), que.end());

	if (que.size() != 0 && (cntQue >= 30 || !SE::IsPlaying(prev)))
	{
		if (SE::IsPlaying(prev))
		{
			SE::Stop(prev);
		}
		SetMessage(que[0]->message);
		ChangeAnim(que[0]->animation);
		SE::Play(que[0]->voice, SoundConfig::VolumeVoice);
		prev = que[0]->voice;
		que.pop_front();
		cntQue = 0;
	}
}

//=====================================
// �`��۔���̃Z�b�g
//=====================================
void GuideViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=====================================
// ���b�Z�[�W�Z�b�g
//=====================================
void GuideViewer::SetMessage(const std::string &message)
{
	// �C�x���g���b�Z�[�W������������s
	if (message.empty()) return;

	ChangeAnim(GuideActor::AnimState::TalkingTypeB);

	callOutViewer->Set(message);
}