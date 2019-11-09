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
#include "../../Field/ActorLoader.h"

//=====================================
// �R���X�g���N�^
//=====================================
CrossJunctionActor::CrossJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::CrossTag[currentLevel].c_str(), mesh);

	type = Field::Model::Junction;
}

//=====================================
// �f�X�g���N�^�i���b�V���̊J���͊��N���X�Łj
//=====================================
CrossJunctionActor::~CrossJunctionActor()
{
}
