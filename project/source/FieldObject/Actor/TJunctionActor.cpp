//=====================================
//
// T�W�����N�V�����A�N�^�[[TJunctionActor.h]
// �@�\�FT���H3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "TJunctionActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"

//=====================================
// �R���X�g���N�^
//=====================================
TJunctionActor::TJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("TJunction-City", mesh);
		break;
	case Field::World:
		break;
	case Field::Space:
		break;
	default:
		break;
	}

	type = Field::Model::Junction;
}

//=====================================
// �f�X�g���N�^
//=====================================
TJunctionActor::~TJunctionActor()
{
}
