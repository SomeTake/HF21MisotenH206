//=====================================
//
// �}�E���e���A�N�^�[[MountainActor.cpp]
// �@�\�F�R�i�Q���A�u���b�N�z�[���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "MountainActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"

//=====================================
// �R���X�g���N�^
//=====================================
MountainActor::MountainActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case FModel::City:
		//ResourceManager::Instance()->GetMesh("Mountain-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::Road;
}

//=====================================
// �f�X�g���N�^
//=====================================
MountainActor::~MountainActor()
{
}
