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
#include "../../Field/ActorLoader.h"

//=====================================
// �R���X�g���N�^
//=====================================
StraightRoadActor::StraightRoadActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::StraightTag[currentLevel].c_str(), mesh);

	type = Field::Model::Road;
}

//=====================================
// �f�X�g���N�^
//=====================================
StraightRoadActor::~StraightRoadActor()
{
}
