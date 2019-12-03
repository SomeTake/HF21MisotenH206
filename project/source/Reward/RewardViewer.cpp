//=====================================
//
// �����[�h�r���A�[[RewardViewer.cpp]
// �@�\�F�e�����[�h��\������N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "RewardViewer.h"
#include "RewardController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "AchieveViewer.h"

//=====================================
// �R���X�g���N�^
//=====================================
RewardViewer::RewardViewer() :
	achieved()
{
	achieveViewer = new AchieveViewer();
}

//=====================================
// �f�X�g���N�^
//=====================================
RewardViewer::~RewardViewer()
{
	SAFE_DELETE(achieveViewer);
}

//=====================================
// �X�V
//=====================================
void RewardViewer::Update()
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
void RewardViewer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	achieveViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// �����[�h���B�m�F
//=====================================
void RewardViewer::CheckAchieved()
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
void RewardViewer::ResetAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		achieved[RC::Type(i)] = false;
	}
}

