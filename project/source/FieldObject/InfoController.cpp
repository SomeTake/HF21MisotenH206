//=====================================
//
// �C���t�H�R���g���[��[InfoController.cpp]
// �@�\�FInfoActor�̃R���g���[���N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "InfoController.h"

//=====================================
// �R���X�g���N�^
//=====================================
InfoController::InfoController()
{
	
}

//=====================================
// �f�X�g���N�^
//=====================================
InfoController::~InfoController()
{
	for (auto& map : LinkInfoMap)
	{
		SAFE_DELETE(map.second);
	}
	LinkInfoMap.clear();
}

//=====================================
// �X�V
//=====================================
void InfoController::Update()
{
	for (auto& map : LinkInfoMap)
	{
		map.second->Update();
	}
}

//=====================================
// �`��
//=====================================
void InfoController::Draw()
{
	for (auto& map : LinkInfoMap)
	{
		map.second->Draw();
	}
}

//=====================================
// �������N���x���̃Z�b�g�A���x���A�b�v
//=====================================
void InfoController::SetLinkLevel(const Field::Model::PlaceData& data)
{
		// ��v����v�f��Map���ɑ��݂��Ȃ��ꍇ
		if (LinkInfoMap.count(data.key) == 0)
		{
			LinkInfoActor* link = new LinkInfoActor(data.key.ConvertToWorldPosition(), data.townLevel);
			LinkInfoMap.emplace(data.key, link);
		}
		// ���݂���ꍇ�A���x�����X�V���邾��
		else
		{
			LinkInfoMap.at(data.key)->SetLevel(data.townLevel);
		}
}