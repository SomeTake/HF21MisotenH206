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
#include "../../Field/ActorLoader.h"

//=====================================
// �R���X�g���N�^
//=====================================
MountainActor::MountainActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::MountainTag[currentLevel].c_str(), mesh);

	type = Field::Model::Mountain;
}

//=====================================
// �f�X�g���N�^
//=====================================
MountainActor::~MountainActor()
{
}
