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
InfoController::InfoController(Field::FieldLevel currentLevel)
{
	current = currentLevel;
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
	LPDIRECT3DDEVICE9 device = GetDevice();
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (auto& map : LinkInfoMap)
	{
		map.second->Draw();
	}

	device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// �������N���x���̃Z�b�g�A���x���A�b�v
//=====================================
void InfoController::SetLinkLevel(const Field::PlaceData& data)
{
		// ��v����v�f��Map���ɑ��݂��Ȃ��ꍇ
		if (LinkInfoMap.count(data.key) == 0)
		{
			LinkInfoActor* link = new LinkInfoActor(data.key.ConvertToWorldPosition(), data.townLevel, current);
			LinkInfoMap.emplace(data.key, link);
		}
		// ���݂���ꍇ�A���x�����X�V���邾��
		else
		{
			LinkInfoMap.at(data.key)->SetLevel(data.townLevel);
		}
}

//=====================================
// �S�Ă̒��̃����N���x���̃Z�b�g�A���x���A�b�v
//=====================================
void InfoController::SetAllLinkLevel(const std::vector<Field::PlaceData>& vec)
{
	for (auto& v : vec)
	{
		SetLinkLevel(v);
	}
}