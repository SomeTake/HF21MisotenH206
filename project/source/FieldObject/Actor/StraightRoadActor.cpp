//=====================================
//
// �X�g���[�g���[�h�A�N�^�[[StraightRoadActor.cpp]
// �@�\�F�܂������ȓ��p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "StraightRoadActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"

//=====================================
// �R���X�g���N�^
//=====================================
StraightRoadActor::StraightRoadActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("StraightRoad-City", mesh);
		break;
	case Field::World:
		break;
	case Field::Space:
		break;
	default:
		break;
	}

	type = Field::Model::Road;
}

//=====================================
// �f�X�g���N�^
//=====================================
StraightRoadActor::~StraightRoadActor()
{
}
