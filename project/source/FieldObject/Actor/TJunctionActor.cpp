//=====================================
//
// T�W�����N�V�����A�N�^�[[TJunctionActor.h]
// �@�\�FT���H3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "TJunctionActor.h"
#include "../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
TJunctionActor::TJunctionActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("TJunction-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}
}

//=====================================
// �f�X�g���N�^
//=====================================
TJunctionActor::~TJunctionActor()
{
}
