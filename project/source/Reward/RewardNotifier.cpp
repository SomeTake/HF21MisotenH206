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

	Debug::Begin("RewardCheck");
	Debug::Text("ButtonMashing %s", RewardController::Instance()->CheckAchieved(RC::Type::ButtonMashing) ? "true" : "false");
	Debug::Text("Destructer %s", RewardController::Instance()->CheckAchieved(RC::Type::Destructer) ? "true" : "false");
	Debug::Text("Artist %s", RewardController::Instance()->CheckAchieved(RC::Type::Artist) ? "true" : "false");
	Debug::Text("Linker %s", RewardController::Instance()->CheckAchieved(RC::Type::Linker) ? "true" : "false");
	Debug::Text("MinusMaster %s", RewardController::Instance()->CheckAchieved(RC::Type::MinusMaster) ? "true" : "false");
	Debug::Text("PlusMaster %s", RewardController::Instance()->CheckAchieved(RC::Type::PlusMaster) ? "true" : "false");
	Debug::Text("Pioneer %s", RewardController::Instance()->CheckAchieved(RC::Type::Pioneer) ? "true" : "false");
	Debug::Text("MasterAI %s", RewardController::Instance()->CheckAchieved(RC::Type::MasterAI) ? "true" : "false");
	Debug::Text("MinusComplete %s", RewardController::Instance()->CheckAchieved(RC::Type::MinusComplete) ? "true" : "false");
	Debug::Text("PlusComplete %s", RewardController::Instance()->CheckAchieved(RC::Type::PlusComplete) ? "true" : "false");
	Debug::End();
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
		if (achieved[i])
			continue;

		if (RewardController::Instance()->CheckAchieved(RC::Type(i)))
		{
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

