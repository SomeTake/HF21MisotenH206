//=====================================
//
// RewardNotifier�N���X[RewardNotifier.cpp]
// �@�\�F�Q�[���������[�h�B����ʒm����N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "RewardNotifier.h"
#include "RewardController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "AchieveViewer.h"
#include "../Viewer/GameScene/GuideViewer/GuideViewer.h"

//=====================================
// �R���X�g���N�^
//=====================================
RewardNotifier::RewardNotifier() :
	achieved()
{
	achieveViewer = new AchieveViewer();
}

//=====================================
// �f�X�g���N�^
//=====================================
RewardNotifier::~RewardNotifier()
{
	SAFE_DELETE(achieveViewer);
}

//=====================================
// �X�V
//=====================================
void RewardNotifier::Update()
{
	CheckAchieved();
	achieveViewer->Update();
}

//=====================================
// �`��
//=====================================
void RewardNotifier::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	achieveViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// �����[�h���B�m�F
//=====================================
void RewardNotifier::CheckAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		// ���ɕ\�����Ă����烊�^�[��
		if (achieved[i])
			continue;

		if (RewardController::Instance()->IsAchieved(RC::Type(i)))
		{
			GuideViewer::Instance()->SetData("���т��������܂���",
				GuideActor::AnimState::TalkingTypeB,
				SoundConfig::SEID(i + (int)SoundConfig::SEID::ButtonMashing));
			SE::Play(SoundConfig::SEID::Achieve, 1.0f);

			achieved[i] = true;
			achieveViewer->SetIndex(i);
			achieveViewer->SetActive();
		}
	}
}

//=====================================
// �����[�h���B�m�F�̃��Z�b�g
//=====================================
void RewardNotifier::ResetAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		achieved[RC::Type(i)] = false;
	}
}

