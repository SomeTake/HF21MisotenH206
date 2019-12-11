//=====================================
//
// �V�e�B�A�N�^�[[CityActor.cpp]
// �@�\�F�s�s�i���A���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CityActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/MophingMeshContainer.h"

#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"

//=====================================
// �R���X�g���N�^
//=====================================
CityActor::CityActor()
	: PlaceActor(),
	useMorphing(false)
{
	type = Field::Model::Town;

	morphingMesh = new MorphingMeshContainer();
}

//=====================================
// �f�X�g���N�^
//=====================================
CityActor::~CityActor()
{
	SAFE_DELETE(morphingMesh);
}

//=====================================
// ����������
//=====================================
void CityActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel)
{
	using Field::Actor::ActorLoader;
	if (currentLevel == Field::FieldLevel::City)
	{
		for (int i = 0; i < 3; i++)
		{
			ResourceManager::Instance()->GetMesh(ActorLoader::CityTownTag[i].c_str(), morphingMesh);
			morphingMesh->RegisterVertex(i);
		}
		morphingMesh->SetCurrent(0);
		morphingMesh->SetNext(1);
		useMorphing = true;
	}
	else if (currentLevel == Field::FieldLevel::World)
	{
		for (int i = 0; i < 3; i++)
		{
			ResourceManager::Instance()->GetMesh(ActorLoader::WorldTownTag[i].c_str(), morphingMesh);
			morphingMesh->RegisterVertex(i);
		}
		morphingMesh->SetCurrent(0);
		morphingMesh->SetNext(1);
		useMorphing = true;
	}
	else
	{
		ResourceManager::Instance()->GetMesh(ActorLoader::CityTag[currentLevel].c_str(), mesh);
		useMorphing = false;
	}


	PlaceActor::Init(pos, currentLevel);
}

//=====================================
// �I������
//=====================================
void CityActor::Uninit()
{
	morphingMesh->Reset();

	PlaceActor::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CityActor::Update()
{
	t = Math::WrapAround(-0.5f, 1.5f, t + 0.02f);
	PlaceActor::Update();
}

//=====================================
// �`�揈��
//=====================================
void CityActor::Draw()
{
	if (useMorphing)
	{
		morphingMesh->SetChange(t);
		morphingMesh->Draw(transform->GetMatrix());
	}
	else
	{
		PlaceActor::Draw();
	}
}
