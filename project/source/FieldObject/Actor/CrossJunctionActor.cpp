//=====================================
//
// �N���X�W�����N�V�����A�N�^�[[CrossJunctionActor.cpp]
// �@�\�F�\���H3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CrossJunctionActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"

//=====================================
// �R���X�g���N�^
//=====================================
CrossJunctionActor::CrossJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("CrossJunction-City", mesh);
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
// �f�X�g���N�^�i���b�V���̊J���͊��N���X�Łj
//=====================================
CrossJunctionActor::~CrossJunctionActor()
{
}
