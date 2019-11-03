//=====================================
//
// �u���b�W�A�N�^�[[BridgeActor.cpp]
// �@�\�F���i���[�v�z�[���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "BridgeActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"

//=====================================
// �R���X�g���N�^
//=====================================
BridgeActor::BridgeActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("Bridge-City", mesh);
		break;
	case Field::World:
		break;
	case Field::Space:
		break;
	default:
		break;
	}

	type = Field::Model::Bridge;
}

//=====================================
// �f�X�g���N�^
//=====================================
BridgeActor::~BridgeActor()
{
}