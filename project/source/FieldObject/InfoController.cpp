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
void InfoController::SetLinkLevel(const Field::FieldPosition& key, const int& townLevel)
{
		// ��v����v�f��Map���ɑ��݂��Ȃ��ꍇ
		if (LinkInfoMap.count(key) == 0)
		{
			LinkInfoActor* link = new LinkInfoActor(key.ConvertToWorldPosition(), townLevel);
			LinkInfoMap.emplace(key, link);
		}
		// ���݂���ꍇ�A���x�����X�V���邾��
		else
		{
			LinkInfoMap.at(key)->SetLevel(townLevel);
		}
}