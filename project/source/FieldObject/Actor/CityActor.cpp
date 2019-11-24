//=====================================
//
// �V�e�B�A�N�^�[[CityActor.cpp]
// �@�\�F�s�s�i���A���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CityActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"

//=====================================
// �R���X�g���N�^
//=====================================
CityActor::CityActor()
	: PlaceActor()
{
	type = Field::Model::Town;
}

//=====================================
// �f�X�g���N�^
//=====================================
CityActor::~CityActor()
{
}

//=====================================
// ����������
//=====================================
void CityActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel)
{
	using Field::Actor::ActorLoader;
	ResourceManager::Instance()->GetMesh(ActorLoader::CityTag[currentLevel].c_str(), mesh);

	PlaceActor::Init(pos, currentLevel);
}
